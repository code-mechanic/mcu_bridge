# MCU BRIDGE

Bridging multiple MCUs with one SDK

### Start the Docker container

```C
make docker_start # One time execution is fine
```

### Stop the Docker container

```C
make docker_stop
```

### Docker troubleshoot

If there is any issue like below then probably there should be docker login required.

**ISSUE:**

```
Error response from daemon: denied
make: *** [Makefile:46: docker_start] Error 1
```

**SOLUTION:**

```
docker login ghcr.io -u <GITHUB_USERNAME>

Password for login is Personal access token generated in GITHIB
```

#### Build SDK

```C
make build_sdk
```

#### Clean SDK

```C
make clean
```
