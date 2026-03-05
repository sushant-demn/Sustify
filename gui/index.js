const volumeSlider = document.querySelector('.volume-slider');
const volumeValueDisplay = document.getElementById('volume-value');
const progressBar = document.querySelector('.progress-bar');

async function getPath() {
    let response = await window.searchFile();
    console.log(response);
    if (!response || response.trim() === "selection cancelled") {
        console.log("User canceled file selection.");
        return;
    }
    let title = await window.getTitle();
    changeTitle(title);
    progressLoop();

}

function changeTitle(title) {
    // '.' finds the class, '#' finds an ID. 
    // This returns the single element directly.
    const titleElement = document.querySelector('.song-title');

    // Safety check: always make sure the element actually exists
    if (titleElement) {
        titleElement.textContent = title;
    } else {
        console.error("Element .song-title not found in the DOM!");
    }
}

async function playPause() {
    let response = await window.stopStart();
}

volumeSlider.addEventListener('input', async function (e) {
    const newVolume = e.target.value;
    let response = await window.volumeChange(newVolume);
    volumeValueDisplay.textContent = newVolume + '%';

});


function updateProgressBar(pBar, value, time) {

    pBar.querySelector(".progress-fill").style.width = `${value}%`;
    pBar.querySelector(".time-stamp").textContent = time;

}

function formatTime(rawSeconds) {
    const minutes = Math.floor(rawSeconds / 60);
    let seconds = Math.floor(rawSeconds % 60);

    if (seconds < 10) {
        seconds = "0" + seconds;
    }
    return minutes + ":" + seconds;
}

async function progressLoop() {
    let duration = await window.getSongLength();

    setInterval(async () => {
        let currentTime = await window.getCursor();

        let value = (currentTime / duration) * 100;


        updateProgressBar(progressBar, value, formatTime(currentTime));
    })
}

progressBar.addEventListener('click', async (e) => {
    const totalWidth = progressBar.clientWidth;

    const clickX = e.offsetX;

    const percentage = clickX / totalWidth;
    console.log(percentage);
    await window.seekSound(percentage);
});