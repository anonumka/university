window.onload = function ()
{
	var ta = document.getElementById('input_area');
	var tb = document.getElementById('clear_btn');
	
	socket = io.connect("http://127.0.0.1:3000");
	
	ta.addEventListener('input', event => {
		console.log(event.target.innerText[event.target.innerText.length - 1]);
		$('.addition_text').css("background-color", "transparent");
		socket.emit('text_edit', { cur_text: event.target.innerText });
	});
	
	tb.addEventListener('click', event => {
		clear_textarea();
		socket.emit('clear');
	});
	
	var tt = '';
	var lastStringCur = '';
	var lastStringNew = '';
	
	socket.on('text_edit', function (data) {
		console.log('len data = ' + data.cur_text.length + ', len ta = ' + ta.innerText.length + ', len tt = ' + tt.length);
		
		for (let i = 0; i < data.cur_text.length; i++)
		{
			if ( (i !== data.cur_text.length - 1) && (data.cur_text[i] !== '\n') ) {
				tmp = tmp + data.cur_text[i];
			}
			else {
				tmp = tmp + data.cur_text[i];
				lastStringNew = tmp;
				tmp = '';
			}
		}
		
		console.log('lastStringCur = ' + lastStringCur + ', lastStringNew = ' + lastStringNew);
		if (data.cur_text.length === 0) {
			console.log(1);
			console.log(data.cur_text.length);
			ta.innerText = '';
			
			tt = data.cur_text;
			lastStringCur = lastStringNew;
		}
		else if ( ((tt.length - data.cur_text.length) >= 1) || ((data.cur_text.length - tt.length) >= 2) 
				|| (lastStringNew.lastIndexOf(lastStringCur) === 0)) {
			console.log(2);
			ta.innerText = '';
			
			var tmp = '';
			for (let i = 0; i < data.cur_text.length; i++)
			{
				if ( (i !== data.cur_text.length - 1) && (data.cur_text[i] !== '\n') ) {
					console.log(i + ', len = ' + data.cur_text.length);
					tmp = tmp + data.cur_text[i];
				}
				else {
					tmp = tmp + data.cur_text[i];
					$('#input_area').append('<div class="addition_text" style="background-color: red;">' + tmp + '</div>');
					tmp = '';
				}
			}
			
			tt = data.cur_text;
			lastStringCur = lastStringNew;
		}
		else if (data.cur_text[data.cur_text.length - 1] === '\n') {
			console.log(3);
			$('#input_area').append('<div></div>');
			
			tt = data.cur_text;
			lastStringCur = lastStringNew;
		}
		else {
			console.log(4);
			if ($('#input_area div').length > 0) {
				$('#input_area div').last().css("background-color", "red");
				$('#input_area div').last().append(data.cur_text[data.cur_text.length - 1]);
			}
			else {
				$('#input_area').append('<div class="addition_text" style="background-color: red;">' + data.cur_text[data.cur_text.length - 1] + '</div>');
			}
			
			tt = data.cur_text;
			lastStringCur = lastStringNew;
		}
	});
	
	socket.on('clear', function (data) {
		clear_textarea();
	});
	
	function clear_textarea() {
		document.getElementById('input_area').innerHTML = "";
		tt = '';
		lastStringCur = '';
	}
	
	socket.on('load', function (data) {
		console.log('load func');
		var tmp = '';
		for (let i = 0; i < data.cur_text.length; i++)
		{
			if ( (i !== data.cur_text.length - 1) && (data.cur_text[i] !== '\n') ) {
				console.log(i + ', len = ' + data.cur_text.length);
				tmp = tmp + data.cur_text[i];
			}
			else {
				tmp = tmp + data.cur_text[i];
				$('#input_area').append('<div class="addition_text" style="background-color: red;">' + tmp + '</div>');
				tmp = '';
			}
		}
	});
}




