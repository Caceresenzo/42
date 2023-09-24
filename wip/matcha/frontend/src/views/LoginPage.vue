<script lang="ts" setup>
import { ref } from 'vue';
import { useMatchaStore } from '@/store';

const store = useMatchaStore();

const id = ref(store.id);

id.value = 5;

</script>

<template>
  <div class="flex h-screen">
    <div class="m-auto w-1/3 h-fit">
      <header>
        <h1 class="text-2xl text-center pb-12">Sign in to Matcha</h1>
      </header>
      <main>
        <form class="mx-auto p-4 bg-light font-darker">
          <div class="form-field">
            <label for="username">Username</label>
            <input type="text" id="username" />
          </div>
          <div class="form-field">
            <label for="password">Password</label>
            <input type="password" id="password" />
          </div>
          <button type="submit" class="btn w-full bg-primary">Sign in</button>
        </form>
      </main>
    </div>
  </div>
</template>
