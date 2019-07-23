#include "ui/WaveformSelectorWidget.hpp"

namespace ui {

    WaveformSelectorWidget::WaveformSelectorWidget(QWidget *parent) {
        setTitle(tr("WaveForm"));
        setup();
    }

    WaveformSelectorWidget::~WaveformSelectorWidget() {

    }

    void WaveformSelectorWidget::setOscType(engine::WaveTypes type) {
        switch(type) {
            case engine::WaveTypes::SINE:
                sinButton->toggle();
                break;
            case engine::WaveTypes::TRIANGLE:
                triButton->toggle();
                break;
            case engine::WaveTypes::SAWTOOTH:
                sawButton->toggle();
                break;
            case engine::WaveTypes::SQUARE:
                squButton->toggle();
                break;
            default:
                break;
        }
    }

    void WaveformSelectorWidget::setup() {
        sinButton = new QRadioButton(tr("Sin"));
        triButton = new QRadioButton(tr("Triangle"));
        sawButton = new QRadioButton(tr("Sawtooth"));
        squButton = new QRadioButton(tr("Square"));

        connect(sinButton, SIGNAL(toggled(bool)), this, SLOT(toggleSin(bool)));
        connect(triButton, SIGNAL(toggled(bool)), this, SLOT(toggleTri(bool)));
        connect(sawButton, SIGNAL(toggled(bool)), this, SLOT(toggleSaw(bool)));
        connect(squButton, SIGNAL(toggled(bool)), this, SLOT(toggleSqu(bool)));

        vBox = new QVBoxLayout;
        vBox->addWidget(sinButton);
        vBox->addWidget(triButton);
        vBox->addWidget(sawButton);
        vBox->addWidget(squButton);
        this->setLayout(vBox);
    }

    void WaveformSelectorWidget::toggleSin(bool checked) {
        if(!checked)
            return;

        emit oscTypeToggled(engine::WaveTypes::SINE);
    }

    void WaveformSelectorWidget::toggleTri(bool checked) {
        if(!checked)
            return;

        emit oscTypeToggled(engine::WaveTypes::TRIANGLE);
    }

    void WaveformSelectorWidget::toggleSaw(bool checked) {
        if(!checked)
            return;

        emit oscTypeToggled(engine::WaveTypes::SAWTOOTH);
    }

    void WaveformSelectorWidget::toggleSqu(bool checked) {
        if(!checked)
            return;

        emit oscTypeToggled(engine::WaveTypes::SQUARE);
    }
}