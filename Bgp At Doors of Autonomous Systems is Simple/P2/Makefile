__APPLY_MODE="static"
.PHONY: __apply
__apply:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if [ -f "$$hname.sh" ]; then \
			echo "apply \`$$hname\` to \`$$container_id\`"; \
			cat $$hname.sh | docker exec -i $$container_id bash -s - "$(__APPLY_MODE)"; \
		fi \
	done

.PHONY: apply-static
apply-static:
	@make --silent __APPLY_MODE="static" __apply

.PHONY: apply-dynamic-multicast
apply-dynamic-multicast:
	@make --silent __APPLY_MODE="dynamic multicast" __apply

.PHONY: show-router
show-router:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if echo "$$hname" | grep -q "routeur_"; then \
			echo "---\ncontainer id:" $$container_id; \
			echo "hostname:" $$hname; \
			echo "vxlan:"; \
			docker exec $$container_id ip -d link show vxlan10; \
			echo "macs:"; \
			docker exec $$container_id brctl showmacs br0; \
		fi \
	done

.PHONY: ping-host
ping-host:
	@for container_id in $$(docker ps --quiet); \
	do \
		hname=$$(docker exec $$container_id hostname); \
		if echo "$$hname" | grep -q "host_"; then \
			echo "---\ncontainer id:" $$container_id; \
			echo "hostname:" $$hname; \
			echo "ifconfig:"; \
			docker exec $$container_id ifconfig eth1; \
			echo "ping:"; \
			if echo "$$hname" | grep -q -- "-1"; then \
				docker exec $$container_id ping -c 4 30.1.1.2; \
			elif echo "$$hname" | grep -q -- "-2"; then \
				docker exec $$container_id ping -c 4 30.1.1.1; \
			else \
				echo 'unknown host?'; \
			fi \
		fi \
	done
