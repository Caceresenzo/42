IMAGE_NAME = frr

build:
	docker build --tag $(IMAGE_NAME) image/

show:
	@for container_id in $$(docker ps --quiet); \
	do \
		echo "---\ncontainer id:" $$container_id; \
		echo "hostname:" $$(docker exec $$container_id hostname); \
		echo "processes:"; \
		docker exec $$container_id ps; \
	done

.PHONY: build show
