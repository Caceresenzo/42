alias ws-set='echo Updated current workspace to: $(echo $(pwd) | tee ~/.current_workspace)'
alias ws='if test -f ~/.current_workspace; then echo "Going to workspace: $(cat ~/.current_workspace)"; cd "$(cat ~/.current_workspace)"; else echo "Workspace not set."; fi'
alias ws-unset='rm -f ~/.current_workspace; echo "Unset workspace."'