﻿using ServiceLayer;
using ServiceLayer.DTO;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace App_Smart_Home_Prototipo.Electrical.Screens
{
    public partial class HomeDeviceScreen : Form
    {
        public HomeDeviceScreen()
        {
            InitializeComponent();

            comboBoxNewType.Items.AddRange(Services.HomeDeviceService.GetHomeDeviceTypes());

            UpdateHomeDevices();
        }

        private void UpdateHomeDevices()
        {
            listBoxHomeDevices.Items.Clear();
            listBoxHomeDevices.Items.AddRange(Services.HomeDeviceService.GetHomeDevices());
        }

        private void AddHomeDevice(object sender, EventArgs e)
        {
            string name = textBoxNewName.Text;
            string type = comboBoxNewType.Text;

            Services.HomeDeviceService.AddHomeDevice(name, type);
            UpdateHomeDevices();
        }

        private void RemoveHomeDevice(object sender, EventArgs e)
        {
            HomeDeviceDTO homeDevice = (HomeDeviceDTO)listBoxHomeDevices.SelectedItem;

            Services.HomeDeviceService.RemoveHomeDevice(homeDevice.Id);
        }

        private void ChangeHomeDeviceInformation(object sender, EventArgs e)
        {
            HomeDeviceDTO homeDevice = (HomeDeviceDTO)listBoxHomeDevices.SelectedItem;
            textBoxNameHomeDevice.Text = homeDevice.Name;
            textBoxTypeHomeDevice.Text = homeDevice.Type;

            listBoxOperations.Items.Clear();
            listBoxOperations.Items.AddRange(Services.OperationService.GetHomeDeviceOperation(homeDevice.Id));
        }

        private void ChangeNameHomeDevice(object sender, EventArgs e)
        {
            HomeDeviceDTO homeDevice = (HomeDeviceDTO)listBoxHomeDevices.SelectedItem;

            Services.HomeDeviceService.SetNameHomeDevice(homeDevice.Id, textBoxNameHomeDevice.Text);
        }


    }
}