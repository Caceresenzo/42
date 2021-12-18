// ==UserScript==
// @name         42 Slots Notifier
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  try to take over the world!
// @author       ecaceres
// @match        https://projects.intra.42.fr/projects/*/slots?team_id=*
// @icon         https://www.google.com/s2/favicons?domain=42.fr
// @grant        GM_notification
// @run-at       document-start
// ==/UserScript==

/// Installation
// 1. Install Tampermonkey: https://chrome.google.com/webstore/detail/tampermonkey/dhdgffkkebhmkfjojejmpbldmpobfkfo
// 2. Click on the extension
// 3. Click on "Dashboard"
// 4. Create a new script
// 5. Paste the content of this script in Tampermonkey
// 6. Save (CTRL + S)

/// Usage
// You need to go on the defence subscription page, the script will automatically start.
// (you will be able to see a little 1 (one) on the Tampermonkey extension's icon)

/// How does it works?
// The script will refresh the page every 5 seconds.
// If a defence has been found, a notification will appear at the bottom right of the screen.
// Clicking on it will take you back to the correct tab.
// The cells will be colored to allow an easier visibility of the current day.
// You just have to select the slot you want, then register to it as you normally would do.

function colorTable(color, hours) {
    const {
        end,
        start
    } = hours

    const pad = (value) => {
        return value.toString().padStart(2, '0');
    }

    const today = new Date().toISOString().split('T')[0];
    const activeHours = Array
        .from({
            length: (end - start) * 2 + 1
        }, (_, index) => start + (index / 2))
        .map((x) => {
            const hour = Math.floor(x)
            const minutes = (x % 1) * 60

            return `${pad(hour)}:${pad(minutes)}:00`
        });

    ((handler) => {
        document.addEventListener("load", handler);

        if (!handler()) {
            const interval = setInterval(() => {
                if (handler()) {
                    clearInterval(interval);
                }
            }, 100)
        }
    })((event) => {
        const elements = document.querySelectorAll(`[data-date='${today}']`);

        for (const element of elements) {
            element.style.backgroundColor = color;
        }

        for (const hour of activeHours) {
            const element = document.querySelector(`[data-time='${hour}']`)

            if (element) {
                element.style.backgroundColor = color;
            }
        }

        return elements.length != 0
    })
}

(function() {
    'use strict';

    const settings = {
        detector: {
            restrictToToday: true
        },
        coloring: {
            enabled: true,
            color: '#4444FF10',
            hours: {
                start: 10,
                end: 19
            }
        }
    }

    const project = window.location.href.match(/projects\/(.*?)\/slots/)?.[1] || '<unknown> project'

    const handle = (responseText) => {
        const response = JSON.parse(responseText)
        let slotCount = response.length

        if (settings.detector.restrictToToday) {
            const today = new Date().toISOString().split('T')[0]

            slotCount = response.filter((slot) => new Date(slot.start).toISOString().split('T')[0] == today).length
        }

        if (slotCount) {
            GM_notification({
                title: project,
                text: `Found ${slotCount} correction!`,
                onclick: () => {
                    window.focus();
                }
            });

            const { coloring } = settings
            if (coloring.enabled) {
                colorTable(coloring.color, coloring.hours);
            }
        } else {
            setTimeout(() => location.reload(), 5000)
        }
    }

    (function(open) {
        window.XMLHttpRequest.prototype.open = function() {
            this.addEventListener("readystatechange", function() {
                if (this.readyState == 4) {
                    handle(this.responseText)
                }
            }, false);
            open.apply(this, arguments);
        };
    })(window.XMLHttpRequest.prototype.open);
})();