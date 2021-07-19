'use strict';

export const ardUIInstance = new Promise(resolve => {
	addEventListener('load', async () => {
		if (typeof ardUI !== 'undefined') {
			await ardUI().then(ardUI => {
				setTimeout(() => {
					document.getElementById('splash').classList.add('invisible');
					resolve(ardUI);
				}, 1000);
			});
		} else {
			setTimeout(() => {
				document.getElementById('splash-load-error').classList.remove('d-none');
				document.getElementById('splash-animation').classList.add('invisible');
			}, 1000);
		}
	});
});


export const click = {
	down: false,
	x: 0,
	y: 0
};


export function cIterate(collection, cb) {
	for (let it = collection.begin(); it.notEquals(collection.end()); it = it.increment()) {
		cb(it.value());
	}
}


addEventListener('load', () => {
	const canvas = document.getElementById('builder-canvas');
	const context = canvas.getContext('2d');
	context.textBaseline = 'top';

	function getColor(colorCode) {
		return '#' + colorCode.toString(16).padStart(6, '0');
	}


	window.display = {
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

		drawPixel(x, y, colorCode) {
			context.fillStyle = getColor(colorCode);
			context.fillRect(x, y, 1, 1);
		},

		drawLine(x1, y1, x2, y2, colorCode) {
			context.strokeStyle = getColor(colorCode);
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
});
