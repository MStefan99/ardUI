//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_SCREEN_H
#define ARDUI_SCREEN_H

class screen {
public:
    void setContentView();
    virtual void onCreate() = 0;
    virtual void onStart();
    virtual void onRestart();
    virtual void onResume();

    virtual void onPause();
    virtual void onStop();
    virtual void onDestroy();
};

#endif //ARDUI_SCREEN_H
