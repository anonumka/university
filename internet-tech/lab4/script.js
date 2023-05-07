// First part of task

var canvas = document.getElementById('box');
var context = canvas.getContext('2d');
context.fillStyle = "pink";
context.fillRect(0, 0, canvas.width, canvas.height);

var figures = [
	["circle",50,50,10],
	["square",150,50,25],
	["ellipse",200,200,30,40]
];

//Круг
context.beginPath();
context.arc(figures[0][1], figures[0][2], figures[0][3], 0, 2 * Math.PI, false);
context.fillStyle = 'yellow';
context.fill();

//Прямоугольник
context.beginPath();
context.strokeStyle = 'red';
context.lineWidth = 2;
context.strokeRect(figures[1][1], figures[1][2], figures[1][3], figures[1][3]);

//Эллипс
context.beginPath();
context.fillStyle = "#10A13F"
context.ellipse(figures[2][1], figures[2][2], figures[2][3], figures[2][4], 0, 0, 2 * Math.PI);
context.fill();

//Кривая Безье
context.beginPath();
context.strokeStyle = 'white';
context.moveTo(100, 200);
context.bezierCurveTo(170, 150, 10, 50, 100, 300);
context.stroke();

// Second part of task
// draw
const ctx = canvas.getContext('2d');
let coord = { x: 0, y: 0 };
var color = "#00FF00";

function changeColorOnGreen() {
	color = "#00FF00";
}

function changeColorOnBlue() {
	color = "#0000FF";
}

function changeColorOnRed() {
	color = "#FF0000";
}

document.addEventListener('mousedown', start);
document.addEventListener('mouseup', stop);

function start(event) {
  document.addEventListener('mousemove', draw);
  coord.x = event.clientX - canvas.offsetLeft;
  coord.y = event.clientY - canvas.offsetTop;
}

function stop() {
  document.removeEventListener('mousemove', draw);
}

function draw(event) {
  ctx.beginPath();
  ctx.lineWidth = 5;
  ctx.lineCap = 'round';
  ctx.strokeStyle = color;
  ctx.moveTo(coord.x, coord.y);
  coord.x = event.clientX - canvas.offsetLeft;
  coord.y = event.clientY - canvas.offsetTop;
  ctx.lineTo(coord.x, coord.y);
  ctx.stroke();
}

// anim
var canvas2 = document.getElementById('box-2');
var context2 = canvas2.getContext('2d');
canvas2.style.backgroundColor = "black";
var circle = {
    center: {
        x: 250,
        y: 250
    },
    radius: 50,
    speed: 2
}
var progress = 0;

function loading() {
    context2.clearRect(0, 0, canvas2.width, canvas2.height);

    progress += 0.01;
    if (progress > 1) {
        progress = 0;
    }

    drawCircle(progress);

    requestAnimationFrame(loading);
}
loading();

function drawCircle(progress) {
    context2.beginPath();
    var start = accelerateInterpolator(progress) * circle.speed;
    var end = decelerateInterpolator(progress) * circle.speed;
    context2.arc(circle.center.x, circle.center.y, circle.radius, (start - 0.5) * Math.PI, (end - 0.5) * Math.PI);
    context2.lineWidth = 3;
    context2.strokeStyle = "white";
    context2.fill();
    context2.stroke();
}

function accelerateInterpolator(x) {
    return x * x;
}

function decelerateInterpolator(x) {
    return 1 - ((1 - x) * (1 - x));
}



























