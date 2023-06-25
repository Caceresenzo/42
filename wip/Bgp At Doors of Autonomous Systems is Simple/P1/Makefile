.PHONY: images
images:
	docker build --tag badass-router image/router
	docker build --tag badass-host image/host

.PHONY: show
show:
	@for container_id in $$(docker ps --quiet); \
	do \
		echo "---\ncontainer id:" $$container_id; \
		echo "hostname:" $$(docker exec $$container_id hostname); \
		echo "processes:"; \
		docker exec $$container_id ps; \
	done
