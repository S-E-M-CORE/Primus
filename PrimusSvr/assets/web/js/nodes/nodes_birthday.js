/*
  Wir speichern alle Note Elemente mit ihrem Text und prioritäten als Objekt.
*/
let notes = []; // Ein Leeres Array

/*  document ist ein Schnittschelle die jede geladene Webseite die in den Browser geladen wird. 
    Dauzu dient Sie auch als "Entry point"/"Einstiegspunkt" in die Webseiteinhalt. 
    Was der DOM tree ist.
*/

function addNote() {
  const newNoteInput = document.getElementById('newNote');  // bekommen das Elment 
  const noteText = newNoteInput.value.trim();   // Wir speichern den Wert von newNoteInput nochmal als getrimmte Version.
  if (noteText !== '') {
    const note = {
      text: noteText,
      priority: 0 // Default priority
    };
    notes.push(note);
    renderNotes();
    newNoteInput.value = '';
  }
}


function editNote(index) {
  const newText = prompt('Gib bitte den neuen Text ein: ');
  if (newText !== null && newText.trim() !== '') {
    notes[index].text = newText.trim();
    renderNotes();
  }
}


function renderNotes() {
  const noteList = document.getElementById('noteList');
  noteList.innerHTML = '';
  notes.forEach((note, index) => {
    const listItem = document.createElement('li');
    listItem.classList.add('list-group-item', 'd-flex', 'justify-content-between', 'align-items-center');

    const noteText = document.createElement('span');
    noteText.innerText = note.text;

    // erstellt den HTML Container
    const buttonsContainer = document.createElement('div');
    buttonsContainer.classList.add('col-1');

    // erstellt ein Edit button
    const editButton = document.createElement('button');    // Erstellen ein Edit Button.
    createEditButton(editButton, index);                    // Design des Edit Button.

    // erstellt ein Delete button
    const deleteButton = document.createElement('button');  // Erstellen ein Delete Button.
    createDeleteButton(deleteButton, index);                // Design des Delete Button.

    buttonsContainer.appendChild(editButton);               // wir fügen den Edit Button dem buttonsContainer hinzu.
    buttonsContainer.appendChild(deleteButton);             // wir fügen den Delete Button dem buttonsContainer hinzu.

    listItem.appendChild(noteText);                         
    listItem.appendChild(buttonsContainer);                 // wir fügen den buttonsContainer in den listItem Container.

    noteList.appendChild(listItem);
  });
}

function createEditButton(Button, index) {
  Button.classList.add('btn', 'btn-primary', 'btn-sm', 'mr-2');
  Button.innerText = 'Edit';
  Button.addEventListener('click', () => editNote(index)); // => ist eine "anonymous Function". => ist das gleiche wie function() ist nur ein andere Schreibweise.
}

function createDeleteButton(Button, index) {

  Button.classList.add('btn', 'btn-danger', 'btn-sm');
  Button.innerText = 'Delete';
  Button.addEventListener('click', () => deleteNote(index));
}


function deleteNote(index) {
  if (confirm('Möchtest du wirklich die Noitzen löschen?')) {
    notes.splice(index, 1);
    renderNotes();
  }
}

function deleteAllNote() {
  if (confirm('Möchtest du wirklich ALLE Geburtstagsnotizen löschen?')) {
    notes = [];             // Setzt das Array notes auf ein leeres Array, um alle Notizen zu löschen
    renderNotes();          // Aktualisiert die Anzeige, um die gelöschten Notizen zu entfernen
  }
}

function getlength()
{
  return notes.length;
}