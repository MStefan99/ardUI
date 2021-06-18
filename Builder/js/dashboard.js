'use strict';

let ardUIInstance;

function redrawDisplay() {
	const builderInterface = new ardUIInstance.BuilderInterface();
	builderInterface.getCurrentActivity().getRootView().invalidate();
	context.textBaseline = 'top';
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
			console.log(builderInterface.getCurrentActivity().getRootView());

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
	const splashErrorText = document.getElementById('splash-load-error');
	const splashAnimation = document.getElementById('splash-animation');

	splashErrorText.classList.remove('d-none');
	splashAnimation.classList.add('d-none');
}