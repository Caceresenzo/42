.PHONY: apply-router
apply-router:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if echo "$$hname" | grep -qv "host_"; then \
			echo "apply \`$$hname\` to \`$$container_id\`"; \
			cat $$hname.sh | docker exec -i $$container_id bash; \
		fi; \
	done;

.PHONY: apply-host
apply-host:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if echo "$$hname" | grep -q "host_"; then \
			echo "apply \`$$hname\` to \`$$container_id\`"; \
			cat $$hname.sh | docker exec -i $$container_id bash; \
		fi; \
	done;

.PHONY: watch-bgp
HOST=_ecaceres-2
watch-bgp:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if [ "$$hname" = '$(HOST)' ]; then \
			echo "watching \`$$hname\` from \`$$container_id\`"; \
			watch -n 0.1 "echo 'do show bgp l2vpn evpn' | docker exec -i $$container_id vtysh;"; \
		fi \
	done
