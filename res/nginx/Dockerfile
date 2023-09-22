FROM debian:buster

RUN apt-get update && apt-get install -y \
    nginx \
    php-cgi \
    python3

RUN mkdir -p /usr/share/nginx/html/
RUN chown -R www-data:www-data /usr/share/nginx/html/

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
