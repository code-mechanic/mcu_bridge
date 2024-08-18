### How to push/pull docker image

1. Create a dedicated personal access token for ghcr login **(One time effort for rest of life)**
2. With the created token login to docker using below command
   * `docker login ghcr.io --username <github_username> --password <token>`
3. Build the docker image using below command
   - Template command :  `docker build -t ghcr.io/<github_username>/<image_name>:<version> <path to dockerfile>`
   - Suggested :  `docker build -t ghcr.io/code-mechanic/microchip_pic_mcu_family:latest ./docker`
4. Push the docker image to github using below command
   * `docker push ghcr.io/code-mechanic/microchip_pic_mcu_family:latest`
5. Create and run a new container from an image. If image is not present then it will automatically do pull.
   * `docker run ghcr.io/code-mechanic/microchip_pic_mcu_family:latest`
