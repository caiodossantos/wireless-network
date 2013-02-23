﻿using DomoticNetwork.EEPROM;
using DomoticNetwork.NetworkModel;
using System;
using System.IO;

namespace DomoticNetwork
{
    class Program
    {
        static void Main(string[] args)
        {
            //EEPROMEXAMPLE
            Network network = new Network();
            network.AddNode();
            network.Nodes[0].NodeShield.AddTimeEvent(new TimeEvent(new Event(), 11, 11, 05));
            network.Nodes[0].NodeShield.AddTimeEvent(new TimeEvent(new Event(0xFF, new Byte[4] { 0x55, 0x55, 0x55, 0x55 }), 11, 11, 30));
            network.Nodes[0].NodeShield.AddTimeEvent(new TimeEvent(new Event(0xFF, new Byte[4] { 0x11, 0x22, 0x33, 0x44 }), 11, 11, 15));
            var add = network.Nodes[0].NodeAddress;
            Generator generatorEEPROM = new Generator(network, add);
            byte[] EEPROM = generatorEEPROM.GenerateEEPROM();
            //guardamos el bin
            File.WriteAllBytes("ex.bin", EEPROM);
            //guardamos el hex
            Binary.SaveBin2Hex(EEPROM);
            Console.WriteLine("DONE");
            Console.ReadLine();



            ////MODULE EXAMPLE
            //PluginLoader ml = new PluginLoader();
            ////Llamo al método "method" de cada módulo
            //foreach (IPlugin m in ml.Modules)
            //{
            //    m.method();
            //}
            ////END MODULE
            //Console.WriteLine("End");
            //Console.ReadLine();
        }
    }
}
