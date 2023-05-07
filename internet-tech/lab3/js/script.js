// First part of task
console.log("Date: " + Date());

let arr = [
	{name: "apple", count: 5, price: 70},
	{name: "orange", count: 10, price: 90},
]

let count = 0;
arr.forEach(function(object)
{
	count = count + object.count * object.price;
});

console.log("Sum of object equal " + count);

let arr2 = {
	bill: arr,
	result: count
};

console.log(JSON.stringify(arr2));

// Second part of task
function addText() {
	let list = document.getElementsByClassName('nav_link');
	for (let i=0; i < list.length; i++){
		document.getElementById('text_area').append(list[i].innerHTML + " ");
	}
}

function animCircle() {
	if (document.getElementById("id-box").style.animation == "")
	{
		document.getElementById("id-box").style.animation = "move_box 4s infinite";
	}
	else {
		document.getElementById("id-box").style.animation = "";
	}
}

function searchItem() {
	let list = document.getElementsByClassName('nav_link');
	let stext = document.getElementById("search-text").value;
	for (let i=0; i<list.length; i++){
		if (list[i].innerHTML.indexOf(stext) != -1)
		{
			document.getElementsByClassName('nav_link')[i].style.color = "red";
		}
		else
		{
			document.getElementsByClassName('nav_link')[i].style.color = "";
		}
	}
}