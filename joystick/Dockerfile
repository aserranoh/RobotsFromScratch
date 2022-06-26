
FROM python:3.11.0b3-alpine
WORKDIR /app
ENV HTTP_PORT=8888
ENV DST_ADDR=localhost
ENV UDP_PORT=5555
ENV JOYSTICK_COLOR=red
COPY *.py *.js *.html *.png ./
CMD python3 joystick.py $HTTP_PORT $DST_ADDR $UDP_PORT

