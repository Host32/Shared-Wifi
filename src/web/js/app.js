        		(function (d, s, id) {
        		    var js, fjs = d.getElementsByTagName(s)[0];
        		    if (d.getElementById(id)) return;
        		    js = d.createElement(s);
        		    js.id = id;
        		    js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.4&appId=1632881616953299";
        		    fjs.parentNode.insertBefore(js, fjs);
        		}(document, 'script', 'facebook-jssdk'));

        		window.fbAsyncInit = function () {
        		    FB.init({
        		        appId: '1632881616953299',
        		        cookie: true, // enable cookies to allow the server to access the session
        		        xfbml: true, // parse social plugins on this page
        		        status: true,
        		        version: 'v2.5'
        		    });
        		};

        		function fb_login() {
        		    FB.login(function (response) {

        		        if (response.authResponse) {

        		            checkLike();

        		            //access_token = response.authResponse.accessToken; //get access token
        		            //user_id = response.authResponse.userID; //get FB UID

        		        } else {
        		            //user hit cancel button
                            showModal(1);
        		            //console.log('User cancelled login or did not fully authorize.');

        		        }
        		    }, {
        		        scope: 'publish_actions, user_birthday, user_likes, user_location, public_profile, email'
        		    });
        		}

        		function captureUserInfo() {
        		    FB.api(
        		        '/me',
        		        'GET', {
        		            "fields": "id,name,link,email,birthday,location,gender"
        		        },
        		        function (response) {
        		            var str = "</br><b>Name</b> : " + response.name + "<br>";
        		            str += "<b>Link: </b>" + response.link + "<br>";
        		            str += "<b>ID: </b>" + response.id + "<br>";
        		            str += "<b>Email: </b> " + response.email + "<br>";
        		            str += "<b>Aniversário: </b> " + response.birthday + "<br>";
        		            str += "<b>Locale: </b> " + response.location.name + "<br>";
        		            str += "<b>Gender: </b> " + response.gender;

        		            return str;
        		        });
        		}


        		function checkLike() {
        		    FB.api("me/likes/549489188538791", function (response) {
        		        if (response.data.length === 1) {
        		            userCheckin();
        		        } else {
                            showModal(2);
        		        }
        		    });

        		}

        		function userCheckin() {
        		    FB.api(
        		        '/me/feed',
        		        'POST', {
        		            "message": "Hello, World! Teste de mensagem.",
        		            "place": "549489188538791"
        		        },
        		        function (response) {
                            if (!response || response.error) {
                                showModal(3);
                            } else {
                                showModal(5);
                            }
        		        }
        		    );
        		}

                function showModal(aux) {
                    var title;
                    var message;
                    var footer;

                    switch (aux) {
                            case (1): // Login
                                title = 'Erro';
                                message = 'Você precisa aceitar as permissões do aplicativo para continuar. Deseja tentar novamente?';
                                footer = '<button type="button" class="btn btn-default" data-dismiss="modal" onClick="fb_login()">Sim</button><button type="button" class="btn btn-default" data-dismiss="modal" onClick="showModal(4)">Não</button>';
                                break;

                            case (2): // Like
                                title = 'Erro';
                                message = '<p>Você ainda não curte nossa página, clique em "Like" e depois em continuar.<br/><iframe src="http://www.facebook.com/plugins/like.php?href=https://www.facebook.com/549489188538791" scrolling="no" frameborder="0" style="border:none; width:450px; height:80px"></iframe></p>';
                                footer = '<button type="button" class="btn btn-default" data-dismiss="modal" onClick="checkLike()">Continuar</button><button type="button" class="btn btn-default" data-dismiss="modal" onClick="showModal(4)">Cancelar</button>';
                                break;

                            case (3): // Check-in
                                title = 'Erro';
                                message = 'Ocorreu um erro ao dar o Check-in. Deseja tentar novamente?';
                                footer = '<button type="button" class="btn btn-default" data-dismiss="modal" onClick="userCheckin()">Sim</button><button type="button" class="btn btn-default" data-dismiss="modal" onClick="showModal(4)">Não</button>';
                                break;

                            case (4): // Error
                                title = 'Internet bloqueada.';
                                message = 'Para desbloquear, faça o Check-in.';
                                footer = '</button><button type="button" class="btn btn-default" data-dismiss="modal">OK</button>';
                                break;

                            case (5): // Free Wifi
                                title = '<h4>Internet Liberada!</h4>';
                                message = 'Obrigado por fazer o Check-in! <br> Aproveite nossa internet gratuita.';
                                footer = '<button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>';
                                break;

                            default:
                                title = 'Erro!';
                                message = 'Ocorreu um erro inesperado.';
                                footer = '<button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>';
                            }
                                        
                    $('#myModal').find('.modal-header').html(title);
                    $('#myModal').find('.modal-body').html(message);
                    $('#myModal').find('.modal-footer').html(footer);
                    
                    $('#myModal').modal();
                }
                