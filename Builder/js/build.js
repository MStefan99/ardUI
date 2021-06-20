'use strict';

import {ardUIInstance, cIterate} from "./ardui-interface.js";


const addText = document.getElementById('add-text');


function removeViews() {
	const container = document.getElementById('view-container');

	while (container.firstChild) {
		container.removeChild(container.firstChild);
	}
}


function addViews(view) {
	const container = document.getElementById('view-container');
	const viewElement = document.createElement('div');

	if (view._viewList) {
		viewElement.classList.add('viewGroup');
	}
	viewElement.classList.add('view');

	viewElement.style.left = view._viewBox.left + 'px';
	viewElement.style.top = view._viewBox.top + 'px';
	viewElement.style.width = view._viewBox.width() + 'px';
	viewElement.style.height = view._viewBox.height() + 'px';

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
