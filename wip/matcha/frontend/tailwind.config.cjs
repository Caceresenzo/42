/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./index.html",
    "./src/**/*.{vue,js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        light: 'rgb(var(--color-light) / <alpha-value>)',
        lighter: 'rgb(var(--color-lighter) / <alpha-value>)',
        dark: 'rgb(var(--color-dark) / <alpha-value>)',
        darker: 'rgb(var(--color-darker) / <alpha-value>)',
        primary: 'rgb(var(--color-primary) / <alpha-value>)',
        secondary: 'rgb(var(--color-secondary) / <alpha-value>)',
        alert: 'rgb(var(--color-alert) / <alpha-value>)',
      },
    }
  },
  plugins: [],
}
