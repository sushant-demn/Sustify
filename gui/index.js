const volumeSlider = document.querySelector('.volume-slider');
const volumeValueDisplay = document.getElementById('volume-value');
const progressBar = document.querySelector('.progress-bar');
const playerControls = document.querySelector('play_pause');
const queuelists = document.querySelector('queuePanel');
const pauseIcon = "./icons/pause.png";
const playIcon = "./icons/play.png";

async function getPath() {
    let response = await window.searchFile();
    console.log(response);
    if (!response || response.trim() === "selection cancelled") {
        console.log("User canceled file selection.");
        return;
    }
    getLatestMeta();
    let title = await window.getTitle();
    // changeTitle(title);
    updateCurrentMeta();
    progressLoop();

}

async function changeTitle(title) {

    const titleElement = document.querySelector('.song-title');
    if (titleElement) {
        titleElement.textContent = title;
    } else {
        console.error("Element .song-title not found in the DOM!");
    }

    await window.volumeChange(volumeValueDisplay.textContent);
}

async function updateCurrentMeta() {
    const meta = await window.getCurrentMeta();
    document.querySelector('.song-title').textContent = meta[0];
    document.querySelector('.song-artist').textContent = meta[1];
    await window.volumeChange(volumeValueDisplay.textContent);

    const prev = document.querySelector(".queueContent .active");
    console.log(prev)
    if (prev)
        prev.classList.remove("active");

    const current = document.getElementById(meta[3]);
    console.log(current);
    if (current)
        current.classList.add("active");

}

async function playPause() {
    let response = await window.stopStart();
    console.log(response);
}

async function next() {
    await window.nextSong();
    updateCurrentMeta();
}
async function previous() {
    await window.backSong();
    updateCurrentMeta();
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
        if (await window.isSongEnding() == "true") {
            next();
        }
    }, 1000)
}

progressBar.addEventListener('click', async (e) => {
    const totalWidth = progressBar.clientWidth;

    const clickX = e.offsetX;

    const percentage = clickX / totalWidth;
    console.log(percentage);
    await window.seekSound(percentage);
});

function changePlayPauseIcon() {
    const iconElement = document.querySelector('.play_pause');
    let currentSrc = iconElement.getAttribute('src');
    if (currentSrc.includes(pauseIcon)) {
        document.querySelector('.play_pause').src = playIcon;
    }
    else {
        document.querySelector('.play_pause').src = pauseIcon;
    }
}

let PanelOpen = false;

function openPanel() {
    if (PanelOpen) {
        document.getElementById('queuePanel').style.right = '-150px';
        document.querySelector('.queueTab').style.right = '0'
        document.querySelector('.left-arrow').style.transform = `rotate(0deg)`;
        PanelOpen = !PanelOpen;
    }
    else {
        document.getElementById('queuePanel').style.right = '0';
        document.querySelector('.queueTab').style.right = '150px'
        document.querySelector('.left-arrow').style.transform = `rotate(180deg)`;
        PanelOpen = !PanelOpen;
    }
}

async function updateQueue() {
    let queueArray = await window.getQueue()
    console.log(queueArray);

    const queueList = document.querySelector(".queueContent");
    queueArray.forEach(element => {
        const li = document.createElement('li');
        li.textContent = element; // Set the text content of the list item
        queueList.appendChild(li); // Append the <li> to the <queueList>
    });
}

firstSong = true;

async function getLatestMeta() {
    if (firstSong == true) {
        document.querySelector('.play_pause').src = pauseIcon;
    }
    firstSong = false;
    let meta = await window.addToQueue();
    console.log(meta);
    const queueList = document.querySelector(".queueContent");
    let ul = queueList.querySelector(".song-list");
    if (!ul) {
        const ulElement = document.createElement('ul');
        ulElement.classList.add("song-list")
        ulElement.style.listStyle = "none";
        ulElement.style.padding = "0";
        queueList.appendChild(ulElement);
    }
    ul = queueList.querySelector(".song-list");
    const li = document.createElement('li');
    li.id = meta[3];
    li.textContent = meta[0];
    ul.appendChild(li);
}

document.addEventListener('DOMContentLoaded', function () {
    const panel = document.getElementById('queuePanel');
    panel.addEventListener('click', async function (event) {
        const clickedItem = event.target.closest('li');
        if (clickedItem) {
            console.log(clickedItem.id);
            res = await window.changeSong(clickedItem.id);
            console.log(res);
            updateCurrentMeta();
        }
    });
});