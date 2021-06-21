'use strict';

import {ardUIInstance, cIterate} from "./ardui-interface.js";


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
		if (!['_viewBox'].includes(propName)
				&& typeof prop !== 'function'
				&& typeof cb === 'function') {
			cb(propName, prop);
		}
		if (typeof prop === 'object') {
			viewPropIterate(prop, cb);
		}
	}
}


function displayViewProperties(view) {
	viewPropIterate(view, (name, prop) => {
		console.log(name, prop);
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
		displayViewProperties(e.target.view);
	});

	container.appendChild(viewElement);

	if (view._viewList) {
		cIterate(view._viewList, child => {
			addViews(child)
		});
	}
}


ardUIInstance.then(ardUI => {
	ardUI._setup();
	ardUI._loop();

	const addText = document.getElementById('add-text');
	const builderInterface = new ardUI.BuilderInterface();
	const currentActivity = builderInterface.getCurrentActivity();

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
		currentActivity.getRootView()._valid = false;
	});
});
