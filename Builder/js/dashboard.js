'use strict';

let ardUIInstance;

function redrawDisplay() {
	const builderInterface = new ardUIInstance.BuilderInterface();
	builderInterface.getCurrentActivity().getRootView().invalidate();
	context.textBaseline = 'top';

	ardUIInstance._loop();
	removeViews();
	addView(builderInterface.getCurrentActivity().getRootView());
}


function cIterate(collection, cb) {
	for (let it = collection.begin(); it.notEquals(collection.end()); it = it.increment()) {
		cb(it.value());
	}
}


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


if (typeof ardUI !== 'undefined') {
	ardUI().then(ardUI => {
		ardUIInstance = ardUI;
		ardUI._setup();
		ardUI._loop();

		setTimeout(() => {
			const splash = document.getElementById('splash');
			splash.classList.add('invisible');

			const builderInterface = new ardUI.BuilderInterface();
			addView(builderInterface.getCurrentActivity().getRootView());

			setInterval(() => {
				ardUI._loop();
			}, 1000 / 10);
		}, 750);

		canvas.addEventListener('mousedown', e => {
			click.down = true;
			click.x = e.offsetX;
			click.y = e.offsetY;
			showMouseCoords(click.x, click.y);
			ardUI._loop();
		});

		canvas.addEventListener('mousemove', e => {
			if (click.down) {
				click.x = e.offsetX;
				click.y = e.offsetY;
				showMouseCoords(click.x, click.y);
				ardUI._loop();
			}
		});

		'mouseup mouseleave'.split(' ').forEach(event => {
			canvas.addEventListener(event, e => {
				click.down = false;
				hideMouseCoords();
				ardUI._loop();
			})
		});
	});
} else {
	addEventListener('load', () => {
		const splashErrorText = document.getElementById('splash-load-error');
		const splashAnimation = document.getElementById('splash-animation');

		splashErrorText.classList.remove('d-none');
		splashAnimation.classList.add('d-none');
	});
}
