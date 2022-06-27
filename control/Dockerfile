
FROM alpine
WORKDIR /app
COPY ./Makefile ./control.c ./
RUN apk update
RUN apk --no-cache --update add build-base
RUN make

FROM alpine
WORKDIR /app
ENV JOYSTICK_PORT=5555
ENV CTL_ADDR=localhost
ENV CTL_PORT=5556
COPY --from=0 /app/control ./
CMD ./control $JOYSTICK_PORT $CTL_ADDR $CTL_PORT

