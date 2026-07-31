using Formula_1_SGBD.Database;
using Formula_1_SGBD.Domain;
using System;
using System.Data.Entity;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Formula_1_SGBD.DAOs
{
    internal class DriverORM
    {
        public void SaveDriver(Driver driver)
        {
            using (var context = new MyContext())
            {
                using (var transaction = context.Database.BeginTransaction())
                {
                    try
                    {
                        driver.ID = 0;
                        context.Drivers.Add(driver);
                        context.SaveChanges();
                        transaction.Commit();
                    }
                    catch (Exception)
                    {
                        transaction.Rollback();
                        throw;
                    }
                }
            }
        }

        public void UpdateDriver(Driver driver)
        {
            using (var context = new MyContext())
            {
                using (var transaction = context.Database.BeginTransaction())
                {
                    try
                    {
                        var existingDriver = context.Drivers.Find(driver.ID);
                        if (existingDriver != null)
                        {
                            existingDriver.Name = driver.Name;
                            existingDriver.Salary = driver.Salary;
                            existingDriver.ContractExpDate = driver.ContractExpDate;
                            existingDriver.TeamID = driver.TeamID;
                            context.SaveChanges();
                        }
                        transaction.Commit();
                    }
                    catch (Exception)
                    {
                        transaction.Rollback();
                        throw;
                    }
                }
            }
        }

        public void DeleteDriver(int driverID)
        {
            using (var context = new MyContext())
            {
                using (var transaction = context.Database.BeginTransaction())
                {
                    try
                    {
                        var driver = context.Drivers.Find(driverID);
                        if (driver != null)
                        {
                            context.Drivers.Remove(driver);
                            context.SaveChanges();
                        }
                        transaction.Commit();
                    }
                    catch (Exception)
                    {
                        transaction.Rollback();
                        throw;
                    }
                }
            }
        }
    }
}
