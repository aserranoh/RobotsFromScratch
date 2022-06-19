
FROM python:3.11.0b3-alpine
WORKDIR /app
ENV HTTP_PORT=8889
ENV UDP_PORT=5556
COPY *.py *.html ./
RUN pip install tornado
CMD python3 simulator.py $HTTP_PORT $UDP_PORT

