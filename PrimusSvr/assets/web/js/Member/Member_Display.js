

/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/


displayMemberData();


async function displayMemberData() 
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000/api/member/${memberId}`);

        const memberData = await apiClient.getMemberById(memberId);

        updateHTML(memberData);
    } catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}

function updateHTML(memberData) 
{
    document.getElementById('FirstName').textContent = `Vorname: ${memberData.firstName}`;
    document.getElementById('LastName').textContent = `Nachname: ${memberData.lastName}`;
    document.getElementById('date').textContent = `Geburtstag: ${memberData.birthDate}`;
    // Füge weitere Daten hinzu und aktualisiere entsprechende HTML-Elemente
}
    


