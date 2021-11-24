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
(function() {
    'use strict';

    console.log("Hello")

    const project = window.location.href.match(/projects\/(.*?)\/slots/)?.[1] || '<unknown> project'

    const handle = (responseText) => {
        const response = JSON.parse(responseText)
        const slotCount = response.length

        if (slotCount) {
            GM_notification({
                title: project,
                text: `Found ${slotCount} correction!`,
                onclick: () => {
                    window.focus();
                }
            });
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