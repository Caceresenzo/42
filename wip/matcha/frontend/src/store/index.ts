import { defineStore } from 'pinia';
import { ref } from 'vue';
import type { Ref } from 'vue';

type State = {
  id: number | undefined;
};

let state : State = {
  id: undefined,
};

export const useMatchaStore = defineStore({
  id: 'matcha',
  state: () => {
    return state;
  },
  actions: {},
  getters: {},
});
