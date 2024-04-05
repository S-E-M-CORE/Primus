    // Funktion, um das Filtermenü zu erstellen
function createFilterMenu() 
{
    const filterMenuContainer = createMenuContainer(); // Erstelle das Hauptcontainer-Element für das Menü
    const activeCheckbox = createCheckbox('Aktive Mitglieder');
    const inactiveCheckbox = createCheckbox('Inaktive Mitglieder');
    addCheckboxes(filterMenuContainer, activeCheckbox, inactiveCheckbox);   // Füge die Checkboxen zum Hauptcontainer hinzu
    const closeButton = createCloseButton(filterMenuContainer);             // Erstelle den Schließen-Button für das Menü
    filterMenuContainer.appendChild(closeButton);
    document.body.appendChild(filterMenuContainer);                         // Füge das Menü zum Dokument hinzu
}

// Funktion zur Erstellung des Hauptcontainers für das Menü
function createMenuContainer() 
{
    const filterMenuContainer = document.createElement('div');
    filterMenuContainer.classList.add('filter-menu');
    return filterMenuContainer;
}

// Funktion zur Erstellung einer Checkbox
function createCheckbox(labelText) 
{
    const checkboxLabel = document.createElement('label');
    const checkboxInput = document.createElement('input');
    checkboxInput.type = 'checkbox';
    checkboxInput.value = labelText.toLowerCase().replace(' ', '-');
    checkboxLabel.appendChild(checkboxInput);
    checkboxLabel.appendChild(document.createTextNode(labelText));
    return checkboxLabel;
}

// Funktion zum Hinzufügen der Checkboxen zum Hauptcontainer
function addCheckboxes(container, ...checkboxes) 
{
    checkboxes.forEach(checkbox => container.appendChild(checkbox)); // Wir legen die checkbox in den Container rein.
}

// Funktion zur Erstellung des Schließen-Buttons
function createCloseButton(menuContainer) 
{
    const closeButton = document.createElement('button');
    closeButton.textContent = 'Schließen';
    closeButton.classList.add('btn', 'btn-dark');
    closeButton.addEventListener('click', () => {
        menuContainer.style.display = 'none';
    });
    return closeButton;
}

/*
    Event-Listener für den Filter-Button
*/
const filterButton = document.querySelector('.btn-filter');
filterButton.addEventListener('click', () => 
{
    const filterMenu = document.querySelector('.filter-menu');
    if (filterMenu) 
    {
        filterMenu.style.display = 'block';
    } else {
        createFilterMenu();
    }
});
