$(document).ready(function(){
$('#buttonLoad').on('click', function(file){
	$.ajax({
		url: "gallery.json",
		dataType: "json",
		success: function(data) {
			file = data;
			progress();
		}
	});

	var load = function(){
		$('#image-collection').empty();
		$('#image-collection').prepend(file.gallery);
		$('#image-collection').append('<br><br>');
		for (var i = 0; i < file.images.length ; i++) {
				$('#image-collection').append('<p>' + file.images[i].name + '</p>');
				$('#image-collection').append('<img class="image" src="images/load-dogs/' + file.images[i].file +'" />');
			}
		}
	//ProgressBar загрузки изображений
	progress = function(){
		var val = 0;
        $( '#image-collection ').empty();
		var interval = setInterval(function() {
			val = val + 1;
			$(".progressBar").progressbar({value: val});
			if (val > 100) {
				clearInterval(interval);
				load();
				alert('Успешно загружено!');
			}
		}, 5);
		$('#other').css('margin-top', '22%');
	}
	});
});
	
//Код слайдера
var slideNow = 1;
var slideCount = 4;
var slideInterval = 3000;
var navBtnId = 0;
var translateWidth = 0;

$(document).ready(function() {
    var switchInterval = setInterval(nextSlide, slideInterval);

    $('#viewport').hover(function() {
        clearInterval(switchInterval);
    }, function() {
        switchInterval = setInterval(nextSlide, slideInterval);
    });

    $('#next-btn').click(function() {
        nextSlide();
    });

    $('#prev-btn').click(function() {
        prevSlide();
    });

    $('.slide-nav-btn').click(function() {
        navBtnId = $(this).index();

        if (navBtnId + 1 != slideNow) {
            translateWidth = -$('#viewport').width() * (navBtnId);
            $('#slidewrapper').css({
                'transform': 'translate(' + translateWidth + 'px, 0)',
                '-webkit-transform': 'translate(' + translateWidth + 'px, 0)',
                '-ms-transform': 'translate(' + translateWidth + 'px, 0)',
            });
            slideNow = navBtnId + 1;
        }
    });
});

function nextSlide() {
    if (slideNow == slideCount || slideNow <= 0 || slideNow > slideCount) {
        $('#slidewrapper').css('transform', 'translate(0, 0)');
        slideNow = 1;
    } else {
        translateWidth = -$('#viewport').width() * (slideNow);
        $('#slidewrapper').css({
            'transform': 'translate(' + translateWidth + 'px, 0)',
            '-webkit-transform': 'translate(' + translateWidth + 'px, 0)',
            '-ms-transform': 'translate(' + translateWidth + 'px, 0)',
        });
        slideNow++;
    }
}

function prevSlide() {
    if (slideNow == 1 || slideNow <= 0 || slideNow > slideCount) {
        translateWidth = -$('#viewport').width() * (slideCount - 1);
        $('#slidewrapper').css({
            'transform': 'translate(' + translateWidth + 'px, 0)',
            '-webkit-transform': 'translate(' + translateWidth + 'px, 0)',
            '-ms-transform': 'translate(' + translateWidth + 'px, 0)',
        });
        slideNow = slideCount;
    } else {
        translateWidth = -$('#viewport').width() * (slideNow - 2);
        $('#slidewrapper').css({
            'transform': 'translate(' + translateWidth + 'px, 0)',
            '-webkit-transform': 'translate(' + translateWidth + 'px, 0)',
            '-ms-transform': 'translate(' + translateWidth + 'px, 0)',
        });
        slideNow--;
    }
}

//Код открытия картинки на весь экран
$(function(){
  $('.slide-img').click(function(event) {
    var i_path = $(this).attr('src');
    $('body').append('<div id="overlay"></div><div id="magnify"><img src="'+i_path+'"><div id="close-popup"><i></i></div></div>');
    $('#magnify').css({
	    left: ($(document).width() - $('#magnify').outerWidth())/3, top: ($(window).height() - $('#magnify').outerHeight())/2
	  });
    $('#overlay, #magnify').fadeIn('fast');
  });

  $('body').on('click', '#close-popup, #overlay', function(event) {
    event.preventDefault();
    $('#overlay, #magnify').fadeOut('fast', function() {
      $('#close-popup, #magnify, #overlay').remove();
    });
  });
});

//Меню аккордеон и смена классов toggleClass
var accordion = function() {
	var data = $(".accordion").attr("data-accordion");
	$(".accordion-header").on("click", function() {
		if (data === "close") {
			$(".accordion-body").slideUp();
			if ($(this).hasClass("active")) {
				$(this).toggleClass("active");
			}
			else {
				$(".accordion-header").removeClass("active");
				$(this).toggleClass("active");
			}
		}
		else {
			$(this).toggleClass("active");
		}
		$(this).next(".accordion-body").not(":animated").slideToggle();
	});
}

accordion();

//Datepicker
$("#datepicker").on('click', function(){
	$("#datepicker").datepicker();
});

//Progressbar
$(function() {
	$(".progressBar").progressbar({
		value: 0
	});
});

//Категории изображений Tabs
$(function() {
	$( "#tabs" ).tabs();
});

//1 вариант - эффект Blind
$( "#buttonBlind" ).click(function() {
  $( "#image-collection" ).toggle( "blind" );
});

$(document).ready(function() {
	$(".ui-progressbar-value").css({ 'background': 'green' });
});