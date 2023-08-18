
nginx:
	docker-compose -f res/nginx/docker-compose.yml up -d

nginx/re:
	docker-compose -f res/nginx/docker-compose.yml restart

nginx/stop:
	docker-compose -f res/nginx/docker-compose.yml down
