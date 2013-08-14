﻿#region Using Statement
using AutoMapper;
using DataLayer;
using DataLayer.Entities;
using ServiceLayer.DTO;
using System;
using System.Drawing;
using System.Linq;
#endregion

namespace ServiceLayer
{
    public class HomeService
    {
        #region GeneralHome

        public void CreateHome()
        {
            if (!Repositories.HomeRespository.IsHomeCreated())
            {
                Home home = new Home();

                Repositories.HomeRespository.Insert(home);
            }
        }

        public bool ExitsHome()
        {
            return Repositories.HomeRespository.IsHomeCreated();
        }

        /// <summary>
        /// Change the name of the Home
        /// </summary>
        /// <param name="newName"></param>
        public void SetHomeName(string newName)
        {
            if (Repositories.HomeRespository.IsHomeCreated())
            {
                var home = Repositories.HomeRespository.GetHome();
                home.Name = newName;

                Repositories.SaveChanges();
            }
        }

        /// <summary>
        /// Get the name of the Home
        /// </summary>
        /// <returns></returns>
        public string GetHomeName()
        {
            if (Repositories.HomeRespository.IsHomeCreated())
                return Repositories.HomeRespository.GetHome().Name;

            return "The Home had not been created";
        }

        /// <summary>
        /// Define the location of a Home
        /// </summary>
        /// <param name="latitude"></param>
        /// <param name="longitude"></param>
        public void SetHomeLocation(float latitude, float longitude)
        {
            if (Repositories.HomeRespository.IsHomeCreated())
            {
                Home home = Repositories.HomeRespository.GetHome();
                home.Location = new Coordenate() { Latitude = latitude, Longitude = longitude };

                Repositories.SaveChanges();
            }
        }

        /// <summary>
        /// Return the location of the home
        /// </summary>
        /// <returns></returns>
        public Coordenate GetHomeLocation()
        {
            if (Repositories.HomeRespository.IsHomeCreated())
                return Repositories.HomeRespository.GetHome().Location;

            return null;
        }

        /// <summary>
        /// Return the MAC of the Pending Nodes
        /// </summary>
        /// <returns>Return string for the MACs</returns>
        public string[] GetPendingNodes()
        {
            throw new NotImplementedException();
            //VICTOR
        }

        /// <summary>
        /// Allow a MAC in the system.
        /// </summary>
        /// <param name="MAC"></param>
        public void AllowPendingNode(string MAC)
        {
            throw new NotImplementedException();
            //VICTOR
        }

        /// <summary>
        /// Deny a MAC in the system
        /// </summary>
        /// <param name="MAC"></param>
        public void DenyPendingNode(string MAC)
        {
            throw new NotImplementedException();
            //VICTOR
        }

        /// <summary>
        /// Unlink Node of the system.
        /// </summary>
        /// <param name="idNode"></param>
        public void UnlinkNode(int idNode)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Update the EEPROMs of all the nodes
        /// </summary>
        public void UpdateConfiguration()
        {
            throw new NotImplementedException();
        }
        #endregion

        #region Zones
        /// <summary>
        /// Return all the Zones
        /// </summary>
        /// <returns>Dictionary ID, Name of zones</returns>
        public ZoneDTO[] GetZones()
        {
            var zones = Repositories.ZoneRepository.GetAll();
            return Mapper.Map<ZoneDTO[]>(zones);
        }

        /// <summary>
        /// Add a zone in the system
        /// </summary>
        /// <param name="zone"></param>
        /// <returns>Devuelve el Id de la zona añadida</returns>
        public int AddZone(string nameZone)
        {
            Zone zone = new Zone();
            zone.Name = nameZone;
            zone.MainView = new View();
            zone.MainView.Name = nameZone;
            zone = Repositories.ZoneRepository.Insert(zone);

            return zone.Id;
        }

        /// <summary>
        /// Remove a Zone at Home
        /// </summary>
        /// <param name="idZone"></param>
        public void RemoveZone(int idZone)
        {
            //NO ES UN METODO SENCILLO DE PROGRAMAR
            throw new NotImplementedException();
        }

        /// <summary>
        /// Change the name of the Zone
        /// </summary>
        /// <param name="idView"></param>
        /// <param name="newName"></param>
        public void SetNameZone(int idZone, string newName)
        {
            var zone = Repositories.ZoneRepository.GetById(idZone);
            zone.Name = newName;
            zone.MainView.Name = newName;

            Repositories.SaveChanges();
        } 

        /// <summary>
        /// Add a View in a concrete Zone at Home
        /// </summary>
        /// <param name="idZone">Identification of the Zone</param>
        /// <param name="nameView">Name of the View</param>
        /// <returns>Return the identification of the new View</returns>
        public int AddView(int idZone, string nameView)
        {
            View view = new View();
            view.Name = nameView;

            Zone zone = Repositories.ZoneRepository.GetById(idZone);
            zone.Views.Add(view);

            Repositories.SaveChanges();

            return Repositories.ViewRepository.GetAll().AsEnumerable().Last().Id;
        }

        /// <summary>
        /// Remove a concrete View
        /// </summary>
        /// <param name="idView"></param>
        public void RemoveView(int idView)
        {
            View view = Repositories.ViewRepository.GetById(idView);
            if(view != null)
                Repositories.ViewRepository.Delete(view);
        }

        /// <summary>
        /// Change the name of the View
        /// </summary>
        /// <param name="idView"></param>
        /// <param name="newName"></param>
        public void SetNameView(int idView, string newName)
        {
            var view = Repositories.ViewRepository.GetById(idView);

            if (view.Id == view.Zone.MainView.Id) //Si es el MainView
                view.Zone.Name = newName;

            view.Name = newName;
        }

        #endregion
    }
}
