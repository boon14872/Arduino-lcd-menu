byte chr_arrowleft[8];
byte chr_arrowright[8];
byte chr_arrowup[8];
byte chr_arrowdown[8];
byte chr_slash[8];
byte chr_indleft[8];
byte chr_indright[8];
byte chr_plus[8];
byte chr_minus[8];

String menu_feature[4][2];
String button_name[5];

// Custom characters
void initializeCharacters()
{

    menu_feature[0][0] = "1 Blue";
    menu_feature[0][1] = "Inside Blue";
    menu_feature[1][0] = "2 Orange";
    menu_feature[1][1] = "Inside Orange";
    menu_feature[2][0] = "3 Red";
    menu_feature[2][1] = "Inside Red";
    menu_feature[3][0] = "4 Yellow";
    menu_feature[3][1] = "Inside Yellow";
    button_name[0] = "Left";
    button_name[1] = "Right";
    button_name[2] = "Up";
    button_name[3] = "Down";
    button_name[4] = "Select";

    chr_arrowleft[0] = 0x00;
    chr_arrowleft[1] = 0x04;
    chr_arrowright[1] = 0x04;
    chr_arrowup[1] = 0x04;
    chr_arrowdown[1] = 0x04;
    chr_slash[1] = 0x01;
    chr_indleft[1] = 0x04;
    chr_indright[1] = 0x04;
    chr_plus[1] = 0x04;
    chr_minus[1] = 0x00;

    // Call the function to initialize the characters
    chr_arrowleft[2] = 0x08;
    chr_arrowleft[3] = 0x1F;
    chr_arrowleft[4] = 0x08;
    chr_arrowleft[5] = 0x04;
    chr_arrowleft[6] = 0x00;
    chr_arrowleft[7] = 0x00;

    chr_arrowright[0] = 0x00;
    chr_arrowright[1] = 0x04;
    chr_arrowright[2] = 0x02;
    chr_arrowright[3] = 0x1F;
    chr_arrowright[4] = 0x02;
    chr_arrowright[5] = 0x04;
    chr_arrowright[6] = 0x00;
    chr_arrowright[7] = 0x00;

    chr_arrowup[0] = 0x00;
    chr_arrowup[1] = 0x04;
    chr_arrowup[2] = 0x0E;
    chr_arrowup[3] = 0x15;
    chr_arrowup[4] = 0x04;
    chr_arrowup[5] = 0x04;
    chr_arrowup[6] = 0x00;
    chr_arrowup[7] = 0x00;

    chr_arrowdown[0] = 0x00;
    chr_arrowdown[1] = 0x04;
    chr_arrowdown[2] = 0x04;
    chr_arrowdown[3] = 0x15;
    chr_arrowdown[4] = 0x0E;
    chr_arrowdown[5] = 0x04;
    chr_arrowdown[6] = 0x00;
    chr_arrowdown[7] = 0x00;

    chr_slash[0] = 0x00;
    chr_slash[1] = 0x01;
    chr_slash[2] = 0x02;
    chr_slash[3] = 0x04;
    chr_slash[4] = 0x08;
    chr_slash[5] = 0x10;
    chr_slash[6] = 0x00;
    chr_slash[7] = 0x00;

    chr_indleft[0] = 0x00;
    chr_indleft[1] = 0x04;
    chr_indleft[2] = 0x08;
    chr_indleft[3] = 0x10;
    chr_indleft[4] = 0x08;
    chr_indleft[5] = 0x04;
    chr_indleft[6] = 0x00;
    chr_indleft[7] = 0x00;

    chr_indright[0] = 0x00;
    chr_indright[1] = 0x04;
    chr_indright[2] = 0x02;
    chr_indright[3] = 0x01;
    chr_indright[4] = 0x02;
    chr_indright[5] = 0x04;
    chr_indright[6] = 0x00;
    chr_indright[7] = 0x00;

    chr_plus[0] = 0x00;
    chr_plus[1] = 0x04;
    chr_plus[2] = 0x04;
    chr_plus[3] = 0x1F;
    chr_plus[4] = 0x04;
    chr_plus[5] = 0x04;
    chr_plus[6] = 0x00;
    chr_plus[7] = 0x00;

    chr_minus[0] = 0x00;
    chr_minus[1] = 0x00;
    chr_minus[2] = 0x00;
    chr_minus[3] = 0x1F;
    chr_minus[4] = 0x00;
    chr_minus[5] = 0x00;
    chr_minus[6] = 0x00;
    chr_minus[7] = 0x00;
}
