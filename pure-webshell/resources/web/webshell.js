document.addEventListener("DOMContentLoaded", () => {
    const logDiv = document.getElementById("log");
    const pingBtn = document.getElementById("pingBtn");

    function log(msg) {
        const p = document.createElement("p");
        p.textContent = `[${new Date().toLocaleTimeString()}] ${msg}`;
        logDiv.appendChild(p);
        logDiv.scrollTop = logDiv.scrollHeight;
    }

    log("Initializing WebChannel...");

    new QWebChannel(qt.webChannelTransport, (channel) => {
        log("WebChannel connected.");

        const coreService = channel.objects.coreService;

        if (coreService) {
            log("CoreService found.");

            // Connect signal
            coreService.pong.connect((msg) => {
                log(`Received signal: ${msg}`);
            });

            // Button click
            pingBtn.addEventListener("click", () => {
                log("Calling CoreService.ping()...");
                coreService.ping();
            });
        } else {
            log("Error: CoreService not found in channel.");
        }
    });
});
