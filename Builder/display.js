'use strict';

const canvas = document.getElementById('builder_canvas');
const context = canvas.getContext('2d');
const mouseInput = document.getElementById('mouse-input');
const spanX = document.getElementById('mouse-x');
const spanY = document.getElementById('mouse-y');


const click = {
	down: false,
	x: 0,
	y: 0
};


const display = {
	getWidth() {
		return canvas.width;
	},

	getHeight() {
		return canvas.height;
	},

	drawLine(x1, y1, x2, y2) {
		context.beginPath();
		context.moveTo(x1, y1);
		context.lineTo(x2, y2);
		context.closePath();
		context.stroke();
	},

	drawText(x, y, text) {
		context.font = '20px sans-serif';
		context.textBaseline = 'top';
		context.fillText(text, x, y);
	},

	isClicked() {
		return click.down;
	},

	getClickX() {
		return click.x;
	},

	getClickY() {
		return click.y;
	}
};


ardUI().then((ardUI) => {
	ardUI._setup();
	ardUI._loop();

	setInterval(() => {
		ardUI._loop();
	}, 5000);

	canvas.addEventListener('mousedown', e => {
		click.down = true;
		mouseInput.style.display = 'block';
		spanX.innerText = (click.x = e.offsetX).toString();
		spanY.innerText = (click.y = e.offsetY).toString();
		ardUI._loop();
	});

	canvas.addEventListener('mousemove', e => {
		if (click.down) {
			spanX.innerText = (click.x = e.offsetX).toString();
			spanY.innerText = (click.y = e.offsetY).toString();
			ardUI._loop();
		}
	});

	'mouseup mouseleave'.split(' ').forEach(event => {
		canvas.addEventListener(event, e => {
			click.down = false;
			mouseInput.style.display = 'none';
			ardUI._loop();
		})
	});
});
