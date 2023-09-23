FROM ubuntu:20.04

RUN apt-get update && \
    apt-get install -y python3 python3-pip curl

RUN mkdir -p /var/www/html
RUN find /var/www/html -type f -exec chmod +x {} \;

WORKDIR /var/www/html

EXPOSE 9001

CMD python3 -m http.server 9001 --cgi
