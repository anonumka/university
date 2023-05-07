VK.init({
    apiId: 51596936
  });

var id = '';

function show_avatar() {
	VK.Api.call('users.get', {uids: id, fields: 'photo_200_orig', v:"5.81"}, function(r) {
	console.log(r);
    if (r.response) {
        $('body').append('<p class="main_text">Аватар: </p><img style="border-radius: 25%;" src="' + r.response[0].photo_200_orig + '">');
		$('body').append('<p>-----------------------------------------------</p>');
		$('body').append('<p class="main_text">Ваши друзья: </p>');
    }
});
}

function auth_vk() {
	VK.Auth.login(function(response) {
		if (response.session) {
			console.log(response.session);
			showAuthData(response.session);

			if (response.settings) {
				console.log(response.settings);
				// Выбранные настройки доступа пользователя если они были запрошены
			}
		} else {
			// Пользователь нажал кнопку Отмена в окне авторизации 
		}
	}); 
}

function showOnlineUsers() {
	VK.Api.call('friends.get', {uids: id, fields: 'photo_50', v:"5.81"}, function(r) {
	console.log(r);
    if (r.response) {
        for (let i = 0; i < r.response.items.length; i++) {
			let tmp = '<div class="list_friends"><img style="border-radius: 100%;" src="' + r.response.items[i].photo_50 + '">';
			tmp += '<p class="surname">' + r.response.items[i].last_name + '<br />';
			tmp += r.response.items[i].first_name + '</p>';
			$('body').append(tmp);
		}
    }
});
}

function showAuthData(data) {
	$('#auth__vk').html("");
	id = data.user.domain;
	$('body').append('<p class="main_text">Добро пожаловать на сайт, ' + data.user.first_name + '</p>');
	$('body').append('<p>Твой ID = <em>' + data.mid + '</em>, а твой псевдоним - <em>' + data.user.domain +'</em></p>');
	show_avatar();
    showOnlineUsers();
}