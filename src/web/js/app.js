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

        		    FB.getLoginStatus(function (response) {
        		        statusChangeCallback(response);
        		    });
        		};

        		function fb_login() {
        		    FB.login(function (response) {

        		        if (response.authResponse) {
        		            console.log(checkLike());
        		            userCheckin();
        		            //console.log(response); // dump complete info
        		            access_token = response.authResponse.accessToken; //get access token
        		            user_id = response.authResponse.userID; //get FB UID

        		            console.log(captureUserInfo());

        		        } else {
        		            //user hit cancel button
        		            console.log('User cancelled login or did not fully authorize.');

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
        		            str += "<b>Gender: </b> " + response.gender + "<br>"

        		            return str;
        		        });
        		}


        		function checkLike() {
        		    FB.api("me/likes/549489188538791", function (response) {
        		        if (response.data.length === 1) {
        		            return 0;
        		        } else {
        		            return 1;
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
        		            if (response.data.length === 1) {
        		                console.log('Fez check-in.');
                                return 0;
        		            } else {
        		                console.log('Não fez check-in.');
                                return 1;
        		            }
        		        }
        		    );
        		}