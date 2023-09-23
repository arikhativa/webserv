
nginx:
	docker-compose -f res/nginx/docker-compose.yml up --build -d

nginx/re:
	docker-compose -f res/nginx/docker-compose.yml restart

nginx/stop:
	docker-compose -f res/nginx/docker-compose.yml down
