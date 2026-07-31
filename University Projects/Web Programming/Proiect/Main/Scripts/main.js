document.addEventListener("DOMContentLoaded", () => {
    initValidations();
    initDependentFields();
    initCarousel();
    initTables();
    initCollapsibleLists();
    initLiveSearch();
});

function initValidations() {
    const forms = document.querySelectorAll('form');
    forms.forEach(form => {
        form.addEventListener('submit', function(e) {
            let isValid = true;
            const inputs = form.querySelectorAll('input, select, textarea');
            inputs.forEach(input => {
                input.classList.remove('input-error');
                if (input.hasAttribute('required') && !input.value.trim()) {
                    isValid = false;
                    input.classList.add('input-error');
                }
                if (input.id === 'numar') {
                    const regex = /^(?:(B\d{2,3}|[A-Z]{2}\d{2})[A-Z]{3}|([A-Z]|MAI){1,2}\d{3,6})$/;
                    if (!regex.test(input.value.trim())) {
                        isValid = false;
                        input.classList.add('input-error');
                    }
                }
                if (input.id === 'client-name') {
                    if (usersData.includes(input.value.trim())) {
                        isValid = false;
                        input.classList.add('input-error');
                    }
                }
                if (input.type === 'password' && input.value.length < 6) {
                    isValid = false;
                    input.classList.add('input-error');
                }
                if (input.type === 'number' && Number(input.value) < 0) {
                    isValid = false;
                    input.classList.add('input-error');
                }
                if (input.id === 'an-fab') {
                    const year = Number(input.value);
                    const currentYear = new Date().getFullYear();
                    if (year < 1990 || year > currentYear) {
                        isValid = false;
                        input.classList.add('input-error');
                    }
                }
            });
            if (!isValid) {
                e.preventDefault();
                alert("Te rugăm să corectezi câmpurile evidențiate cu roșu!");
            }
        });
    });
}

function initDependentFields() {
    const marcaSelect = document.getElementById('marca-select');
    const modelSelect = document.getElementById('model-select');
    if (marcaSelect && modelSelect) {
        for (let marca in autoData) {
            let option = document.createElement('option');
            option.value = marca;
            option.textContent = marca;
            marcaSelect.appendChild(option);
        }
        marcaSelect.addEventListener('change', function() {
            modelSelect.innerHTML = '<option value="">Alege Modelul</option>';
            const selectedMarca = this.value;
            if (autoData[selectedMarca]) {
                autoData[selectedMarca].forEach(model => {
                    let option = document.createElement('option');
                    option.value = model;
                    option.textContent = model;
                    modelSelect.appendChild(option);
                });
                modelSelect.disabled = false;
            } else {
                modelSelect.disabled = true;
            }
        });
    }

    const anInput = document.getElementById('an-fab');
    const dataInput = document.getElementById('data-inspectie');
    if (anInput && dataInput) {
        anInput.addEventListener('input', function() {
            if (this.value >= 2020) {
                let nextYear = new Date().getFullYear() + 1;
                dataInput.min = `${nextYear}-01-01`;
            } else {
                dataInput.min = "";
            }
        });
    }
}

function initCarousel() {
    const container = document.getElementById('carousel-container');
    if (!container) return;
    let currentIndex = 0;
    const slideImg = document.getElementById('carousel-img');
    const slideText = document.getElementById('carousel-text');
    const slideLink = document.getElementById('carousel-link');

    function showSlide(index) {
        if (index < 0) currentIndex = carouselData.length - 1;
        else if (index >= carouselData.length) currentIndex = 0;
        else currentIndex = index;
        const data = carouselData[currentIndex];
        slideImg.src = data.img;
        slideText.textContent = data.text;
        slideLink.href = data.link;
    }

    let timerId = null;
    function startTimer() {
        timerId = setInterval(() => { showSlide(currentIndex + 1); }, 5000);
    }

    function resetTimer() {
        clearInterval(timerId);
        startTimer();
    }

    document.getElementById('carousel-prev').addEventListener('click', () => { 
        showSlide(currentIndex - 1); 
        resetTimer();
    });
    document.getElementById('carousel-next').addEventListener('click', () => {
        showSlide(currentIndex + 1); 
        resetTimer();
    });
    
    startTimer();
    showSlide(0);
}

function initTables() {
    const tbody = document.querySelector('#classic-table tbody');
    if (tbody) {
        function renderTable(data) {
            tbody.innerHTML = '';
            data.forEach(item => {
                let tr = document.createElement('tr');
                tr.innerHTML = `<td>${item.numar}</td><td>${item.marca}</td><td>${item.status}</td><td>${item.problema}</td><td>${item.mecanic}</td><td>${item.data}</td>`;
                tbody.appendChild(tr);
            });
        }
        renderTable(ticketsData);

        const headers = document.querySelectorAll('#classic-table th');
        headers.forEach((th, index) => {
            th.addEventListener('click', () => {
                let isAsc = th.classList.contains('asc');
                headers.forEach(h => h.classList.remove('asc', 'desc'));
                th.classList.add(isAsc ? 'desc' : 'asc');
                const key = Object.keys(ticketsData[0])[index];
                ticketsData.sort((a, b) => {
                    if (a[key] < b[key]) return isAsc ? 1 : -1;
                    if (a[key] > b[key]) return isAsc ? -1 : 1;
                    return 0;
                });
                renderTable(ticketsData);
            });
        });
    }

    const verticalTable = document.getElementById('vertical-table');
    if (verticalTable) {
        const rowHeaders = verticalTable.querySelectorAll('th');
        rowHeaders.forEach((th, rowIndex) => {
            th.addEventListener('click', () => {
                const rows = verticalTable.rows;
                const numCols = rows[0].cells.length;
                let colData = [];
                for (let i = 1; i < numCols; i++) {
                    let col = [];
                    for (let j = 0; j < rows.length; j++) {
                        col.push(rows[j].cells[i].innerText);
                    }
                    colData.push(col);
                }
                let isAsc = th.classList.contains('asc');
                rowHeaders.forEach(h => h.classList.remove('asc', 'desc'));
                th.classList.add(isAsc ? 'desc' : 'asc');
                colData.sort((colA, colB) => {
                    let valA = colA[rowIndex];
                    let valB = colB[rowIndex];
                    return isAsc ? valB.localeCompare(valA) : valA.localeCompare(valB);
                });
                for (let i = 1; i < numCols; i++) {
                    for (let j = 0; j < rows.length; j++) {
                        rows[j].cells[i].innerText = colData[i - 1][j];
                    }
                }
            });
        });
    }
}

function initCollapsibleLists() {
    const listItems = document.querySelectorAll('.rules-list li');
    listItems.forEach(item => {
        const subList = item.querySelector('ul, ol');
        if (subList) {
            item.classList.add('collapsible-parent');
            const span = document.createElement('span');
            span.className = 'toggle-icon';
            span.innerHTML = ' [+] ';
            item.insertBefore(span, item.firstChild);
            span.addEventListener('click', function(e) {
                e.stopPropagation();
                subList.classList.toggle('show');
                span.innerHTML = subList.classList.contains('show') ? ' [-] ' : ' [+] ';
            });
        }
    });
}

function initLiveSearch() {
    const searchInput = document.getElementById('live-search');
    const tbody = document.querySelector('#classic-table tbody');
    if (searchInput && tbody) {
        searchInput.addEventListener('input', function() {
            const query = this.value.toLowerCase();
            const rows = tbody.querySelectorAll('tr');
            rows.forEach(row => {
                const text = row.innerText.toLowerCase();
                if (text.includes(query)) {
                    row.style.display = '';
                } else {
                    row.style.display = 'none';
                }
            });
        });
    }
}