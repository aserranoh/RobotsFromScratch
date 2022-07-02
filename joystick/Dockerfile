
FROM alpine
RUN apk update
RUN apk --no-cache --update add build-base
WORKDIR /app
COPY ./Makefile ./joystick.c ./mongoose.c ./mongoose.h ./
RUN make

FROM scratch
ENV HTTP_PORT=8888
ENV DST_ADDR=localhost
ENV UDP_PORT=5555
ENV JOYSTICK_COLOR=red
COPY --from=0 /app/joystick ./
COPY ./main.html ./joy.js ./joystick-base.png ./
CMD ["/joystick"]
