var component;
var page;

function createMetadataObject(parent, properties) {
    component = Qt.createComponent("qml/MetadataPage.qml");
    page = component.createObject(parent, properties);

    if (page == null) {
        // Error Handling
        console.log("Error creating object");
    }
}
