'use strict';

import {ardUIInstance, cIterate} from "./ardui-interface.js";


const canvas = document.getElementById('builder-canvas');
const context = canvas.getContext('2d');


function removeViews() {
	const container = document.getElementById('view-container');

	while (container.firstChild) {
		container.removeChild(container.firstChild);
	}
}


function addView(view) {
	const container = document.getElementById('view-container');
	const viewElement = document.createElement('div');

	if (view._viewList) {
		viewElement.classList.add('view', 'viewGroup')
	} else {
		viewElement.classList.add('view')
	}

	viewElement.style.left = view._viewBox.left + 'px';
	viewElement.style.top = view._viewBox.top + 'px';
	viewElement.style.width = (view._viewBox.right - view._viewBox.left) + 'px';
	viewElement.style.height = (view._viewBox.bottom - view._viewBox.top) + 'px';

	container.appendChild(viewElement);

	if (view._viewList) {
		cIterate(view._viewList, child => {
			addView(child)
		});
	}
}


ardUIInstance.then(ardUI => {
	ardUI._setup();
	ardUI._loop();

	const builderInterface = new ardUI.BuilderInterface();
	const currentActivity = builderInterface.getCurrentActivity();
	addView(currentActivity.getRootView());

	setTimeout(() => {
		const splash = document.getElementById('splash');
		splash.classList.add('invisible');
	}, 750);


	setInterval(() => {
		if (!currentActivity.getRootView()._valid) {
			ardUI._loop();
			removeViews();
			addView(currentActivity.getRootView());
		}
	}, 100);
});
