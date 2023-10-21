.PHONY: apply
apply:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if [ -f "$$hname.sh" ]; then \
			echo "apply \`$$hname\` to \`$$container_id\`"; \
			cat $$hname.sh | docker exec -i $$container_id bash; \
		fi; \
	done;
