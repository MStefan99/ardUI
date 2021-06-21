'use strict';

import {ardUIInstance, cIterate} from "./ardui-interface.js";


ardUIInstance.then(ardUI => {
	ardUI._setup();
	ardUI._loop();

	const addText = document.getElementById('add-text');
	const builderInterface = new ardUI.BuilderInterface();
	const currentActivity = builderInterface.getCurrentActivity();

	function getFriendlyName(name) {
		if (name.startsWith('_')) {
			name = name.substr(1);
		}
		let friendlyName = name.replace(/^(\w)/, '$1')[0].toUpperCase();

		for (const char of name.substr(1)) {
			if (char.match(/[A-Z]/)) {
				friendlyName = friendlyName + ' ' + char.toLowerCase();
			} else if (char.match(/[a-z0-9]/)) {
				friendlyName += char;
			}
		}

		return friendlyName
				.replace('Min', 'Minimum')
				.replace('Max', 'Maximum');
	}


	function removeViews() {
		const container = document.getElementById('view-container');

		while (container.firstChild) {
			container.removeChild(container.firstChild);
		}
	}


	function viewPropIterate(view, cb) {
		for (const propName in view) {
			// No point in checking for own property since all properties
			// in emscripten are inherited anyway
			const prop = view[propName];
			if (typeof prop !== 'function'
					&& typeof cb === 'function') {
				cb(propName, prop);
			}
			if (typeof prop === 'object') {
				viewPropIterate(prop, cb);
			}
		}
	}


	function displayViewProperties(viewElement) {
		const view = viewElement.view;
		const container = document.getElementById('view-prop-container');

		while (container.firstChild) {
			container.removeChild(container.firstChild);
		}


		viewPropIterate(view, (propName, prop) => {
			const propNameElement = document.createElement('label');
			const propElement = document.createElement('input');

			switch (typeof prop) {
				case "string":
					propElement.setAttribute('type', 'text');
					propElement.addEventListener('change', () => {
						viewElement.view[propName] = propElement.value;
						currentActivity.getRootView().invalidate();
					});
					break;
				case "number":
					if (propName.match(/color/i)) {
						propElement.setAttribute('type', 'color');
						propElement.addEventListener('change', () => {
							viewElement.view[propName] = parseInt(propElement.value
									.substr(1, 6), 16);
							currentActivity.getRootView().invalidate();
						});
					} else {
						propElement.setAttribute('type', 'number');
						propElement.addEventListener('change', () => {
							viewElement.view[propName] = +propElement.value;
							currentActivity.getRootView().invalidate();
						});
					}
					break;
				case "boolean":
					propElement.setAttribute('type', 'checkbox');
					propElement.addEventListener('change', () => {
						viewElement.view[propName] = !!propElement.value;
						currentActivity.getRootView().invalidate();
					});
					break;
				case 'object':
					const groupElement = document.createElement('div');
					groupElement.classList.add('collapsable');
					const id = 'prop_' + getFriendlyName(propName) + '_'
							+ Math.random() * 0xffffff;

					const radioElement = document.createElement('input');
					radioElement.setAttribute('type', 'checkbox');
					radioElement.id = radioElement.name = id;

					const labelElement = document.createElement('label');
					labelElement.innerText = getFriendlyName(propName);
					labelElement.setAttribute('for', id);

					groupElement.appendChild(labelElement);
					groupElement.appendChild(radioElement);
					container.appendChild(groupElement);

					return;  // Needs to have a collapsable div
			}

			propNameElement.innerText = getFriendlyName(propName);
			propElement.value = prop;
			container.appendChild(propNameElement);
			container.appendChild(propElement);
		});
	}


	function addViews(view) {
		const container = document.getElementById('view-container');
		const viewElement = document.createElement('div');
		viewPropIterate(view);

		if (view._viewList) {
			viewElement.classList.add('viewGroup');
		}
		viewElement.classList.add('view');
		viewElement.view = view;

		viewElement.style.left = view._viewBox.left + 'px';
		viewElement.style.top = view._viewBox.top + 'px';
		viewElement.style.width = view._viewBox.width() + 'px';
		viewElement.style.height = view._viewBox.height() + 'px';
		viewElement.addEventListener('click', e => {
			for (const e of container.childNodes) {
				e.classList.remove('selected');
			}
			viewElement.classList.add('selected');
			displayViewProperties(e.target);
		});

		container.appendChild(viewElement);

		if (view._viewList) {
			cIterate(view._viewList, child => {
				addViews(child)
			});
		}
	}


	{ //  Will be run after page load
		addViews(currentActivity.getRootView());

		setTimeout(() => {
			const splash = document.getElementById('splash');
			splash.classList.add('invisible');
		}, 750);

		setInterval(() => {
			if (!currentActivity.getRootView()._valid) {
				ardUI._loop();
				removeViews();
				addViews(currentActivity.getRootView());
			}
		}, 100);

		addText.addEventListener('click', () => {
			currentActivity.getRootView().addView(new ardUI.TextView("text"));
			currentActivity.getRootView().invalidate();
		});
	}
});
