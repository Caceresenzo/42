.PHONY: apply
apply:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if [ -f "$$hname.sh" ]; then \
			while docker logs $$container_id | grep zebra | tail -n 1 | grep down; \
			do \
				echo "zebra not ready for \`$$hname\` in \`$$container_id\`"; \
				sleep 1; \
			done; \
			echo "apply \`$$hname\` to \`$$container_id\`"; \
			cat $$hname.sh | docker exec -i $$container_id bash; \
		fi; \
	done;
