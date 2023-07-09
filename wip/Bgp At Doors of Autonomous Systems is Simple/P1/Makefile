.PHONY: images
images:
	docker build --tag badass-router images/router
	docker build --tag badass-host images/host

.PHONY: show
show:
	@for container_id in $$(docker ps --quiet); \
	do \
		echo "---\ncontainer id:" $$container_id; \
		echo "hostname:" $$(docker exec $$container_id hostname); \
		echo "processes:"; \
		docker exec $$container_id ps; \
	done
