console.log("script.js loaded");

function animateValue(el, value) {
  el.style.transform = "scale(1.08)";
  setTimeout(() => {
    el.textContent = value;
    el.style.transform = "scale(1)";
  }, 120);
}

async function updateStats() {
  const res = await fetch("stats.json?t=" + Date.now(), {
    cache: "no-store"
  });

  const data = await res.json();
  console.log("Fetched data:", data);

  
  const cpuEl = document.getElementById("cpu");
  const cpuValue = data.cpu;

  animateValue(cpuEl, cpuValue.toFixed(2));

  
  cpuEl.classList.remove("cpu-normal", "cpu-warn", "cpu-spike");

  
  if (cpuValue >= 80) {
    cpuEl.classList.add("cpu-spike");
  } else if (cpuValue >= 50) {
    cpuEl.classList.add("cpu-warn");
  } else {
    cpuEl.classList.add("cpu-normal");
  }

  
  document.getElementById("memory").textContent =
    `${data.memory_used} / ${data.memory_total} MB`;

  
  document.getElementById("disk").textContent =
    `${data.disk_used} / ${data.disk_total} GB`;

  
  document.getElementById("uptime").textContent = data.uptime;

  
  const cpuFill = document.querySelector(".cpu-fill");
  if (cpuFill) {
    cpuFill.style.width = `${cpuValue}%`;
  }
}

setInterval(updateStats, 1000);
updateStats();
