
FROM alpine
RUN apk update
RUN apk --no-cache --update add build-base
WORKDIR /app
COPY ./Makefile ./control.c ./
RUN make

FROM scratch
ENV JOYSTICK_PORT=5555
ENV CTL_ADDR=localhost
ENV CTL_PORT=5556
COPY --from=0 /app/control ./
CMD ["/control"]

