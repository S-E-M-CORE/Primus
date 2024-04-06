
/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/

displayController();

async function displayController()
{
    let memberData = await displayMemberData();       // gibt uns das Adresse Jason Objekt.
    //let adresseData = displayAdresseData();     // gibt uns das Adresse Jason Objekt.

    adresseData = 1; // Damit es funktioniert muss auf Sascha warten. 

    updateHTML(memberData, adresseData);        // ändert den angezeigten Text.
}

async function displayMemberData() 
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const memberData = await apiClient.getMemberById(memberId);
        JSON.stringify(memberData);
        return memberData;

    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}

/*
*/ 
async function displayAdresseData()
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const adresseData = await apiClient.getMemberById(memberId);
        JSON.stringify(memberData);
        return memberData;

    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
} 



// async function getuserinput() 
// {
//     // benutzereingaben erfassen
//     let firstname = document.getelementbyid("firstname").value;
//     let lastname = document.getelementbyid("lastname").value;
//     let birthdate = document.getelementbyid("birth_date").value;
//     let postalcode = document.getelementbyid("poz").value;
//     let residence = document.getelementbyid("residence").value;
//     let street = document.getelementbyid("street").value;
//     let housenumber = document.getelementbyid("h_number").value;
//     let email = document.getelementbyid("member_email").value;
//     let phonenumber = document.getelementbyid("telenumber").value;
//     let joindate = document.getelementbyid("date").value;
//     let notes = document.queryselector("textarea").value;
//     let membership = document.queryselector("select").value;
// }



/*
Die Funktion ist dazu alle infomationen die von allen benötigten Jason Objekten kommen  

Parameters:
    memberData - zeigen Vorname
    adresseData - zeigen Postleitzahl, Wohnort, Straßename, Hausnummer
*/
function updateHTML(memberData , adresseData) 
{
    error_DB_Anomalie(memberData, adresseData);     // wir überprüfen die Ressource die wir bekommen haben.

    let currentUserMember   = memberData[0];    // 0 weil wir nur nach einem User Fragen wollen.
    let currentUserAdresse   = adresseData[0];   //
    
    /* 
        currentUserMember
    */
    var inputElement_FirstName = document.getElementById('FirstName');    
    inputElement_FirstName.value = currentUserMember.firstName;           // 
    
    var inputElement_LastName = document.getElementById('LastName');    
    inputElement_LastName.value = currentUserMember.lastName;    

    var inputElement_birth_date = document.getElementById('birth_date');    
    birth_date.value = currentUserMember.birthDate;  


    /*
        currentUserAdresse
    */
    //var inputElement_Poz = document.getElementById('Poz');    
    //inputElement_Poz.value = currentUserAdresse.firstName;           //     
//
    //var inputElement_residence = document.getElementById('residence');    
    //inputElement_residence.value = currentUserAdresse.city;           // 
//
    //var inputElement_street = document.getElementById('street');    
    //inputElement_street.value = currentUserAdresse.street;           // 
//
    //var inputElement_H_Number = document.getElementById('H_Number');    
    //inputElement_H_Number.value = currentUserAdresse.houseNumber;           // 


    /*

    */


    
    // ('Member_email').textContent = ${currentUserMember.email}
    // ('phoneNumber').textContent =  ${currentUserMember.phoneNumber}
    



    //document.getElementById('FirstName').textContent = `Vorname: ${currentUserMember.firstName}`;
    
    //currentUserAdresse
    //document.getElementById('Poz').textContent = `Postleitzahl: ${currentUserAdresse.phoneNumber}`;
}
    
// check for single User.
function error_DB_Anomalie(memberData, adresseData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }

    // if(adresseData[1] !== undefined)
    // {
    //     alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    // }
}



