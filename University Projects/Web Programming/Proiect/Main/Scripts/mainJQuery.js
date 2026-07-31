$(document).ready(function() {
    initValidations();
    initDependentFields();
    initCarousel();
    initTables();
    initCollapsibleLists();
    initLiveSearch();
    initLiveCharCount();
    initLiveFeedback();
    initLiveEmailInput();
});

function initValidations() {
    $('form').on('submit', function(e) {
        let isValid = true;
        
        const $inputs = $(this).find('input, select, textarea');
        
        $inputs.each(function() {
            const $input = $(this);
            $input.removeClass('input-error');
            
            const val = $.trim($input.val());

            if ($input.prop('required') && !val) {
                isValid = false;
                $input.addClass('input-error');
            }
            
            if ($input.attr('id') === 'numar') {
                const regex = /^(?:(B\d{2,3}|[A-Z]{2}\d{2})[A-Z]{3}|([A-Z]|MAI){1,2}\d{3,6})$/;
                if (!regex.test(val)) {
                    isValid = false;
                    $input.addClass('input-error');
                }
            }
            
            if ($input.attr('id') === 'client-name') {
                if (typeof usersData !== 'undefined' && usersData.includes(val)) {
                    isValid = false;
                    $input.addClass('input-error');
                }
            }
            
            if ($input.attr('type') === 'password' && val.length < 6) {
                isValid = false;
                $input.addClass('input-error');
            }
            
            if ($input.attr('type') === 'number' && Number(val) < 0) {
                isValid = false;
                $input.addClass('input-error');
            }
            
            if ($input.attr('id') === 'an-fab') {
                const year = Number(val);
                const currentYear = new Date().getFullYear();
                if (year < 1990 || year > currentYear) {
                    isValid = false;
                    $input.addClass('input-error');
                }
            }
        });

        if (!isValid) {
            e.preventDefault();
            alert("Te rugăm să corectezi câmpurile evidențiate cu roșu!");
        }
    });
}

function initDependentFields() {
    const $marcaSelect = $('#marca-select');
    const $modelSelect = $('#model-select');
    
    if ($marcaSelect.length && $modelSelect.length) {
        $.each(autoData, function(marca, modele) {
            $('<option>').val(marca).text(marca).appendTo($marcaSelect);
        });
        
        $marcaSelect.on('change', function() {
            $modelSelect.empty().append('<option value="">Alege Modelul</option>');
            const selectedMarca = $(this).val();
            
            if (autoData[selectedMarca]) {
                $.each(autoData[selectedMarca], function(index, model) {
                    $('<option>').val(model).text(model).appendTo($modelSelect);
                });
                $modelSelect.prop('disabled', false);
            } else {
                $modelSelect.prop('disabled', true);
            }
        });

        if ($marcaSelect.val()) {
            $marcaSelect.trigger('change');
        }
    }

    const $anInput = $('#an-fab');
    const $dataInput = $('#data-inspectie');
    if ($anInput.length && $dataInput.length) {
        $anInput.on('input', function() {
            if ($(this).val() >= 2020) {
                let nextYear = new Date().getFullYear() + 1;
                $dataInput.attr('min', `${nextYear}-01-01`);
            } else {
                $dataInput.attr('min', "");
            }
        });
    }
}

function initCarousel() {
    const $container = $('#carousel-container');
    if (!$container.length) return;
    
    let currentIndex = 0;
    const $slideImg = $('#carousel-img');
    const $slideText = $('#carousel-text');
    const $slideLink = $('#carousel-link');

    function showSlide(index) {
        if (index < 0) currentIndex = carouselData.length - 1;
        else if (index >= carouselData.length) currentIndex = 0;
        else currentIndex = index;
        
        const data = carouselData[currentIndex];
        $slideImg.attr('src', data.img);
        $slideText.text(data.text);
        $slideLink.attr('href', data.link);
    }

    let timerId = null;
    function startTimer() {
        timerId = setInterval(() => { showSlide(currentIndex + 1); }, 5000);
    }

    function resetTimer() {
        clearInterval(timerId);
        startTimer();
    }

    $('#carousel-prev').on('click', function() { 
        showSlide(currentIndex - 1); 
        resetTimer();
    });
    
    $('#carousel-next').on('click', function() {
        showSlide(currentIndex + 1); 
        resetTimer();
    });
    
    startTimer();
    showSlide(0);
}

function initTables() {
    const $tbody = $('#classic-table tbody');
    if ($tbody.length) {
        function renderTable(data) {
            $tbody.empty();
            $.each(data, function(index, item) {
                $('<tr>').append(
                    $('<td>').text(item.numar),
                    $('<td>').text(item.marca),
                    $('<td>').text(item.status),
                    $('<td>').text(item.problema),
                    $('<td>').text(item.mecanic),
                    $('<td>').text(item.data)
                )
                .css('background-color', item.status === 'Finalizat' ? 'green' : (item.status === 'În Așteptare' ? 'yellow' : ''))
                .appendTo($tbody);
            });
        }
        
        if (typeof ticketsData !== 'undefined') {
            renderTable(ticketsData);
        }

        const $headers = $('#classic-table th');
        $headers.on('click', function() {
            const $th = $(this);
            const isAsc = $th.hasClass('asc');
            
            $headers.removeClass('asc desc');
            $th.addClass(isAsc ? 'desc' : 'asc');
            
            const colIndex = $th.index();
            const key = Object.keys(ticketsData[0])[colIndex];
            
            ticketsData.sort((a, b) => {
                if (a[key] < b[key]) return isAsc ? 1 : -1;
                if (a[key] > b[key]) return isAsc ? -1 : 1;
                return 0;
            });
            renderTable(ticketsData);
        });
    }

    const $verticalTable = $('#vertical-table');
    if ($verticalTable.length) {
        const $rowHeaders = $verticalTable.find('th');
        
        $rowHeaders.on('click', function() {
            const $th = $(this);
            const rowIndex = $th.parent().index();
            const $rows = $verticalTable.find('tr');
            const numCols = $rows.first().children().length;
            
            let colData = [];
            for (let i = 1; i < numCols; i++) {
                let col = [];
                $rows.each(function() {
                    col.push($(this).children().eq(i).text());
                });
                colData.push(col);
            }
            
            let isAsc = $th.hasClass('asc');
            $rowHeaders.removeClass('asc desc');
            $th.addClass(isAsc ? 'desc' : 'asc');
            
            colData.sort((colA, colB) => {
                let valA = colA[rowIndex];
                let valB = colB[rowIndex];
                return isAsc ? valB.localeCompare(valA) : valA.localeCompare(valB);
            });
            
            for (let i = 1; i < numCols; i++) {
                $rows.each(function(j) {
                    $(this).children().eq(i).text(colData[i - 1][j]);
                });
            }
        });
    }
}

function initCollapsibleLists() {
    $('.rules-list li:has(ul, ol)').each(function() {
        const $item = $(this);
        const $subList = $item.children('ul, ol');
        
        $item.addClass('collapsible-parent');
        
        const $span = $('<span>').addClass('toggle-icon').text(' [+] ');
        $item.prepend($span);
        
        $span.on('click', function(e) {
            e.stopPropagation();
            $subList.toggleClass('show');
            // $subList.slideToggle();
            $span.text($subList.hasClass('show') ? ' [-] ' : ' [+] ');
        });
    });
}

function initLiveSearch() {
    const $searchInput = $('#live-search');
    const $statusFilters = $('input[name="status-filter"]');
    
    if ($searchInput.length) {
        $searchInput.on('input', function() {
            const query = $(this).val().toLowerCase();
            
            $('#classic-table tbody tr').each(function() {
                const $row = $(this);
                const text = $row.text().toLowerCase();
                const status = $row.find('td').eq(2).text();
                
                const matchesQuery = text.includes(query);
                const matchesStatus = $statusFilters.filter(':checked').length === 0 || 
                    $statusFilters.filter(`[value="${status}"]`).is(':checked');
                
                $row.toggle(matchesQuery && matchesStatus);
            });
        });

        $statusFilters.on('change', function() {
            $searchInput.trigger('input');
        });
    }
}

function initLiveCharCount() {
    const $textarea = $('#problema');
    const $charCount = $('#char-count');

    $textarea.on('input', function() {
        const length = $(this).val().length;
        $charCount.text(`${length}/200`);
        $(this).toggleClass('input-error', length > 200);
    });
}

function initLiveFeedback() {
    const $feedbackDiv = $('#improvements');
    const $notaSelect = $('#nota');

    $notaSelect.on('change', function() {
        // if ($(this).val() == 1) {
        //     $feedbackDiv.css('display', 'block');
        // }
        // else {            
        //     $feedbackDiv.css('display', 'none');
        // }
        $feedbackDiv.toggle($(this).val() == 1);
    });
}

function initLiveEmailInput() {
    const $newsletterCheckbox = $('input[name="newsletter"]');
    const $emailInput = $('#email');

    $newsletterCheckbox.on('change', function() {
        $emailInput.toggle(this.checked);
    });
}