'use strict';

import {ardUIInstance, click} from "./ardui-interface.js";


const mouseCoords = document.getElementById('mouse-coords');
const canvas = document.getElementById('builder-canvas');


function showMouseCoords(x, y) {
	mouseCoords.innerText = 'Mouse down at (' + x + ', ' + y + ')';
	mouseCoords.style.visibility = 'visible';
}

function hideMouseCoords() {
	mouseCoords.style.visibility = 'hidden';
}


ardUIInstance.then(ardUI => {
	ardUI._setup();
	ardUI._loop();

	setInterval(() => {
		ardUI._loop();
	}, 1000 / 10);

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
