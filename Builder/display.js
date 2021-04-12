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


context.textBaseline = 'top';

addEventListener('load', () => {
	const params = new URLSearchParams(window.location.search);
	if (params.has('width')) {
		canvas.width = +params.get('width');
	}
	if (params.has('height')) {
		canvas.height = +params.get('height');
	}
	context.textBaseline = 'top';
});


function getColor(colorCode) {
	return '#' + colorCode.toString(16).padStart(6, '0');
}


const display = {
	getWidth() {
		return canvas.width;
	},

	getHeight() {
		return canvas.height;
	},

	fill(colorCode) {
		context.fillStyle = getColor(colorCode);
		context.fillRect(0, 0, canvas.width, canvas.height);
	},

	drawLine(x1, y1, x2, y2, colorCode) {
		context.beginPath();
		context.moveTo(x1, y1);
		context.lineTo(x2, y2);
		context.closePath();
		context.stroke();
	},

	drawRect(x1, y1, x2, y2, colorCode) {
		context.strokeStyle = getColor(colorCode);
		context.strokeRect(x1, y1, x2 - x1, y2 - y1);
	},

	fillRect(x1, y1, x2, y2, colorCode) {
		context.fillStyle = getColor(colorCode);
		context.fillRect(x1, y1, x2 - x1, y2 - y1);
	},

	drawText(x, y, text, height, colorCode) {
		context.font = height + 'px sans-serif';
		context.fillStyle = getColor(colorCode);
		context.fillText(text, x, y);
	},

	getTextWidth(text, height) {
		context.font = height + 'px sans-serif';
		return Math.ceil(context.measureText(text).width);
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
	}, 500);

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
